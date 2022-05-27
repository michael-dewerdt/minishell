/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 08:57:53 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/24 08:30:44 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty(char *line)
{
	while (*line)
	{
		if (*line < 9 || (*line > 13 && *line != 32))
			return (0);
		line++;
	}
	return (1);
}

int	handle_status(t_datas *datas, int status)
{
	int	ret;

	if (WIFSIGNALED(status))
	{
		ret = 128 + WTERMSIG(status);
		if (datas->exit_code == 131)
			printf("Quit: 3\n");
	}
	else
		ret = WEXITSTATUS(status);
	return (ret);
}

void	nothing(int sig_num)
{
	(void)sig_num;
}

void	sigs_handler(int sig_num)
{
	if (sig_num == SIGINT)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	halt(t_datas *datas, int ret_code, int silent)
{
	int	i;

	i = 0;
	while (datas->envp[i])
	{
		free(datas->envp[i]);
		i++;
	}
	free(datas->envp);
	clear_history();
	if (!silent)
		printf("exit\n");
	if (silent)
		exit(datas->exit_code);
	exit(ret_code);
}
