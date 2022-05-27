/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:15:59 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/27 09:18:55 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_error(char *cmd, char *msg, char *msg2)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	if (msg2)
		ft_putstr_fd(msg2, 2);
	return (1);
}

int	is_valid_identifier(char *ident, int silent)
{
	int	i;

	i = 0;
	if (ft_isalpha(ident[0]) || ident[0] == '_')
	{
		while (ident[i])
		{
			if (!ft_isalpha(ident[i]) && !ft_isdigit(ident[i])
				&& ident[i] != '_')
			{
				if (!silent && cmd_error("export",
						"not an identifier: ", ident))
					ft_putchar_fd('\n', 2);
				return (0);
			}
			i++;
		}
		return (1);
	}
	if (!silent && cmd_error("export",
			"not an identifier: ", ident))
		ft_putchar_fd('\n', 2);
	return (0);
}
