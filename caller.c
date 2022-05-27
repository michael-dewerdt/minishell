/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caller.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:48:16 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/27 08:48:24 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		call_binary(t_datas *datas, t_command *cmd);
static pid_t	call(t_datas *datas, t_command *cmd);

int	call_builtin(t_datas *datas, t_command *cmd)
{
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (ft_echo(cmd));
	else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (ft_pwd(cmd));
	else if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (ft_cd(datas, cmd));
	else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		return (ft_export(datas, cmd));
	else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (ft_unset(datas, cmd));
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (ft_env(datas, cmd, 0));
	else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (ft_exit(datas, cmd));
	else
		return (-1);
}

static void	call_binary(t_datas *datas, t_command *cmd)
{
	char	**path_dirs;
	char	*path;

	if (ft_strchr(cmd->argv[0], '/'))
		execve(cmd->argv[0], cmd->argv, datas->envp);
	else
	{
		path = get_var_value(datas, "PATH", 4);
		path_dirs = ft_split(path, ':');
		free(path);
		while (path_dirs && *path_dirs)
		{
			path = ft_strjoin_with(*path_dirs, cmd->argv[0], "/");
			execve(path, cmd->argv, datas->envp);
			free(path);
			path_dirs++;
		}
	}
	cmd_error(cmd->argv[0], "command not found\n", NULL);
}

static pid_t	call(t_datas *datas, t_command *cmd)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{	
		if (call_builtin(datas, cmd) == -1)
		{
			if (cmd->fd[0])
			{
				dup2(cmd->fd[0], STDIN_FILENO);
				close(cmd->fd[0]);
			}
			if (cmd->fd[1])
			{
				dup2(cmd->fd[1], STDOUT_FILENO);
				close(cmd->fd[1]);
			}
			if (cmd->ope == PIPE)
				close(cmd->next->fd[0]);
			call_binary(datas, cmd);
		}
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

void	create_pipe(t_command *cmd)
{
	int	pip[2];

	if (cmd->ope != PIPE)
		return ;
	pipe(pip);
	if (!cmd->fd[1])
		cmd->fd[1] = pip[1];
	else
		close(pip[1]);
	if (!cmd->next->fd[0])
		cmd->next->fd[0] = pip[0];
	else
		close(pip[0]);
}

int	caller(t_datas *datas, t_command *cmd)
{
	int		status;

	if (cmd->ope != PIPE && is_builtin(cmd->argv[0]))
		datas->exit_code = call_builtin(datas, cmd);
	else
		cmd->pid = (create_pipe(cmd), call(datas, cmd));
	if (cmd->fd[0])
		close(cmd->fd[0]);
	if (cmd->fd[1])
		close(cmd->fd[1]);
	if (cmd->ope == PIPE)
		caller(datas, cmd->next);
	waitpid(cmd->pid, &status, 0);
	if (cmd->ope != PIPE)
	{
		if (!is_builtin(cmd->argv[0]))
			datas->exit_code = handle_status(datas, status);
		while (cmd->next && !((cmd->ope == AND && !datas->exit_code) \
			|| (cmd->ope == OR && datas->exit_code)))
			cmd = cmd->next;
		if (cmd->next)
			caller(datas, cmd->next);
	}
	return (1);
}
