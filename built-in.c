/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 09:02:57 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/27 08:46:51 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd) + 1;
	if (!ft_strncmp(cmd, "echo", ft_min(cmd_len, 5))
		|| !ft_strncmp(cmd, "pwd", ft_min(cmd_len, 4))
		|| !ft_strncmp(cmd, "cd", ft_min(cmd_len, 3))
		|| !ft_strncmp(cmd, "export", ft_min(cmd_len, 7))
		|| !ft_strncmp(cmd, "unset", ft_min(cmd_len, 6))
		|| !ft_strncmp(cmd, "env", ft_min(cmd_len, 4))
		|| !ft_strncmp(cmd, "exit", ft_min(cmd_len, 5)))
		return (1);
	else
		return (0);
}

int	ft_echo(t_command *cmd)
{
	int	no_nl;
	int	fd_out;
	int	i;

	if (cmd->fd[1])
		fd_out = cmd->fd[1];
	else
		fd_out = 1;
	no_nl = 0;
	i = 1;
	while (cmd->argv[i])
	{
		if (ft_strncmp(cmd->argv[i], "-n", 2) == 0 && i++)
		{
			no_nl = 1;
			continue ;
		}
		ft_putstr_fd(cmd->argv[i], fd_out);
		if (cmd->argv[++i])
			ft_putstr_fd(" ", fd_out);
	}
	if (!no_nl)
		ft_putstr_fd("\n", fd_out);
	return (0);
}

int	ft_pwd(t_command *cmd)
{
	char	*dir;
	int		fd_out;

	if (cmd->fd[1])
		fd_out = cmd->fd[1];
	else
		fd_out = 1;
	dir = ft_calloc(PATHS_MAX_SIZE, sizeof(char));
	getcwd(dir, PATHS_MAX_SIZE);
	ft_putstr_fd(dir, fd_out);
	ft_putstr_fd("\n", fd_out);
	free(dir);
	return (0);
}

int	ft_cd(t_datas *datas, t_command *cmd)
{
	char	*home;

	if (cmd->argc > 2)
		return (cmd_error("cd", "too many arguments\n", NULL));
	if (cmd->argv[1])
	{
		if (access(cmd->argv[1], X_OK))
			return (cmd_error(cmd->argv[0], cmd->argv[1],
					": Permission denied\n"));
		else if (access(cmd->argv[1], F_OK))
			return (cmd_error(cmd->argv[0], cmd->argv[1],
					": Not a directory\n"));
		chdir(cmd->argv[1]);
		return (0);
	}
	else
	{
		home = get_var_value(datas, "HOME", 5);
		if (*home)
			chdir(home);
		else
			return (cmd_error("cd", "HOME not set\n", NULL));
	}
	return (0);
}

int	ft_exit(t_datas *datas, t_command *cmd)
{
	if (cmd->argc == 1)
		halt(datas, EXIT_SUCCESS, 0);
	else if (cmd->argc == 2)
	{
		if (!ft_isnumber(cmd->argv[1]))
		{
			cmd_error("exit", "numeric argument required\n", NULL);
			halt(datas, 2, 0);
		}			
		halt(datas, ft_atoi(cmd->argv[1]) % 255, 0);
	}
	cmd_error("exit", "too many arguments\n", NULL);
	return (EXIT_FAILURE);
}
