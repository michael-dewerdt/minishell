/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:18:30 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/16 09:56:05 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wc_str_cmp(char *wc, char *str)
{
	int	i;
	int	j;
	int	skip ;

	i = 0;
	j = 0;
	skip = (wc[0] != '.' && str[0] == '.');
	while (wc[i] && !skip)
	{
		if (wc[i] == '*' && ++i)
			while (str[j] && str[j] != wc[i])
				j++;
		else if (str[j] != wc[i])
				skip = 1;
		else
		{
			i++;
			j++;
		}
	}
	if (str[j] != wc[i])
		skip = 1;
	return (skip);
}

int	create_wc(t_lexer *lex, char *wc)
{
	DIR				*direct;
	struct dirent	*file;	

	direct = opendir(".");
	file = (readdir(direct), readdir(direct), readdir(direct));
	while (file)
	{
		if (!wc_str_cmp(wc, file->d_name))
			create_token(lex, file->d_name);
		file = readdir(direct);
	}
	closedir(direct);
	lex->wc = 0;
	return (1);
}
