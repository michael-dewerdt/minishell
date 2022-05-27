/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:44:57 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/27 08:59:20 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_register(t_lexer *lex, char **line, char *tmp);

void	tmp_dealer(t_datas *datas, t_lexer *lex, char *line, char *tmp)
{
	int	tmp_i;

	tmp_i = 0;
	while (*line)
	{
		if (check_state(lex, &line))
			continue ;
		if (lex->state != S_QUOTE_ST && lex->deep == 0 && *line == '$'
			&& (ft_isalpha(line[1]) || line[1] == '_' || line[1] == '?'))
			tmp_i = replace_var(datas, &line, tmp, tmp_i);
		else if (check_register(lex, &line, tmp))
			tmp_i = (ft_bzero(tmp, STR_MAX_SIZE), 0);
		else if (!(lex->state == ROOT_ST && lex->deep == 0
				&& (*line == '"' || *line == '\'')))
			tmp[tmp_i++] = *(line++);
	}
	if (!*tmp && (*(line - 1) == '"' || *(line - 1) == '\''))
		lex->empty = 1;
}

t_token	*lexer(t_datas *datas, char *line)
{
	t_lexer	*lex;
	t_token	*ret;
	char	*tmp;

	lex = ft_calloc(1, sizeof(*lex));
	lex->state = ROOT_ST;
	tmp = ft_calloc(STR_MAX_SIZE, sizeof(*tmp));
	tmp_dealer(datas, lex, line, tmp);
	if (lex->type == WORD && lex->wc)
		create_wc(lex, tmp);
	else
		create_token(lex, tmp);
	free(tmp);
	if (lex->state != ROOT_ST)
		ret = NULL;
	else
		ret = lex->tokens;
	free(lex);
	return (ret);
}

int	create_token(t_lexer *lex, char str[])
{
	t_token	*tok;
	t_token	*tmp;
	t_type	type;

	type = lex->type;
	if (lex->next_type)
		lex->type = lex->next_type;
	else
		lex->type = WORD;
	lex->next_type = WORD;
	if (!str[0] && !lex->empty)
		return (0);
	tok = ft_calloc(1, sizeof(*tok));
	tok->type = type;
	tok->value = ft_strdup(str);
	tmp = lex->tokens;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		lex->tokens = tok;
	else
		tmp->next = tok;
	lex->empty = 0;
	return (1);
}

static int	check_ope(t_lexer *lex, char **line, char *tmp)
{
	if (!ft_strncmp(*line, "&&", 2))
	{
		(*line) += 2;
		lex->next_type = AND;
		create_token(lex, tmp);
		return (create_token(lex, "&&"));
	}
	if (!ft_strncmp(*line, "||", 2))
	{
		(*line) += 2;
		lex->next_type = OR;
		create_token(lex, tmp);
		return (create_token(lex, "||"));
	}
	if (**line == '|')
	{
		(*line)++;
		lex->next_type = PIPE;
		create_token(lex, tmp);
		return (create_token(lex, "|"));
	}
	return (0);
}

static int	check_register(t_lexer *lex, char **line, char *tmp)
{
	int	spaces;

	if (lex->state != ROOT_ST || lex->deep > 0)
		return (0);
	spaces = 0;
	if (!*tmp && (*(*line - 1) == '"' || *(*line - 1) == '\''))
		lex->empty = 1;
	while (ft_isspace(**line) && ++spaces)
		(*line)++;
	if (set_redir(lex, line, '>') || set_redir(lex, line, '<'))
		return (create_token(lex, tmp));
	if (check_ope(lex, line, tmp))
		return (1);
	if ((**line == '(' && ++lex->deep) || spaces)
	{
		if (*tmp || lex->empty)
		{
			if (lex->type == WORD && lex->wc)
				return (create_wc(lex, tmp));
			return (create_token(lex, tmp));
		}
		return (1);
	}
	return (0);
}
