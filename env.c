/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:41:29 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/27 08:51:55 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_env(t_datas *datas, int i);

int	ft_unset(t_datas *datas, t_command *cmd)
{
	char	**env;
	int		i;
	int		j;
	int		name_len;

	if (cmd->argc < 2)
		return (1);
	env = datas->envp;
	i = 1;
	while (i < cmd->argc && datas->envp[i - 1])
	{
		name_len = ft_strlen(cmd->argv[i]);
		j = 0;
		while (datas->envp[j])
		{
			env = ft_split(datas->envp[j], '=');
			if (!ft_strncmp(cmd->argv[i], env[0], name_len + 1))
				clean_env(datas, j);
			else if (++j)
				ft_free_split(env);
		}
		i++;
	}
	return (0);
}

int	ft_env(t_datas *datas, t_command *cmd, int declared_pop)
{
	int	i;
	int	fd_out;

	if (cmd->fd[1])
		fd_out = cmd->fd[1];
	else
		fd_out = 1;
	i = 0;
	while (datas->envp[i])
	{
		if (declared_pop)
			ft_putstr_fd("declare -x ", fd_out);
		ft_putstr_fd(datas->envp[i], fd_out);
		ft_putchar_fd('\n', fd_out);
		i++;
	}
	return (0);
}

int	save_var(t_datas *datas, char *argv)
{
	int		i;
	int		name_len;
	char	**env;
	char	**var;

	var = ft_split(argv, '=');
	name_len = ft_strlen(var[0]);
	if (!is_valid_identifier(var[0], 0))
		return (1);
	i = 0;
	while (datas->envp[i])
	{
		env = ft_split(datas->envp[i], '=');
		if (!ft_strncmp(var[0], env[0], name_len + 1))
			datas->envp[i] = (free(datas->envp[i]), NULL);
		else
			i++;
		ft_free_split(env);
	}
	datas->envp[i] = ft_strdup(argv);
	ft_free_split(var);
	return (0);
}

int	ft_export(t_datas *datas, t_command *cmd)
{
	int		i;
	int		tmp;
	int		ret;

	if (cmd->argc < 2 && (ft_env(datas, cmd, 1), 1))
		return (0);
	ret = 0;
	i = 0;
	while (++i < cmd->argc)
	{
		if (!cmd->argv[i][0] || cmd->argv[i][0] == '=')
		{
			ret = 1;
			continue ;
		}
		tmp = save_var(datas, cmd->argv[i]);
		if (tmp)
			ret = tmp;
	}
	return (ret);
}

static void	clean_env(t_datas *datas, int i)
{
	int	j;

	free(datas->envp[i]);
	datas->envp[i] = NULL;
	i = 0;
	j = 0;
	while (i < ENVP_MAX_SIZE)
	{
		if (!datas->envp[i])
		{
			j = 1;
			while (!datas->envp[i + j] && (i + j) < ENVP_MAX_SIZE)
				j++;
			if (i + j == ENVP_MAX_SIZE)
				return ;
			datas->envp[i] = datas->envp[i + j];
			datas->envp[i + j] = NULL;
		}
		i++;
	}
}
