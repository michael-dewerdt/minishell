/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 07:53:17 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/24 08:06:11 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_var(t_datas *datas, char **line, char *tmp, int tmp_i)
{
	int		name_len;
	int		i;
	char	*value;

	if ((*line)[1] == '?')
	{
		value = ft_itoa(datas->exit_code);
		name_len = 2;
	}
	else
	{
		name_len = 1;
		while (ft_isalpha((*line)[name_len])
				|| ft_isdigit((*line)[name_len]) || (*line)[name_len] == '_')
			name_len++;
		value = get_var_value(datas, *line + 1, name_len - 1);
	}
	i = 0;
	while (value[i])
		tmp[tmp_i++] = value[i++];
	tmp[tmp_i] = 0;
	*line += name_len;
	free(value);
	return (tmp_i);
}

char	*expend_str(t_datas *datas, char *line)
{
	char	*tmp;
	int		tmp_i;

	tmp = ft_calloc(STR_MAX_SIZE, sizeof(*tmp));
	if (!tmp)
		free(tmp);
	tmp_i = 0;
	while (*line)
	{
		if (*line == '$')
			tmp_i = replace_var(datas, &line, tmp, tmp_i);
		else
			tmp[tmp_i++] = *(line++);
	}
	return (tmp);
}

char	*get_var_value(t_datas *datas, char *line, int name_len)
{
	int		i;
	char	**env;
	char	*name;
	char	*value;

	name = ft_substr(line, 0, name_len);
	i = 0;
	value = NULL;
	while (datas->envp[i] && !value)
	{
		env = ft_split(datas->envp[i], '=');
		if (!ft_strncmp(name, env[0], name_len + 1))
		{
			if (env[1])
				value = ft_strdup(env[1]);
			else
				value = ft_strdup("");
		}
		++i;
		ft_free_split(env);
	}
	free(name);
	if (!value)
		value = ft_strdup("");
	return (value);
}

int	set_redir(t_lexer *lex, char **line, char ch)
{
	static t_type	type_out[2] = {OUT, ADD};
	static t_type	type_in[2] = {IN, HD};
	t_type			*type;

	if (ch == '>')
		type = type_out;
	else
		type = type_in;
	if (**line == ch && (*line)++)
	{
		if (**line == ch && (*line)++)
			lex->next_type = type[1];
		else
			lex->next_type = type[0];
		return (1);
	}
	return (0);
}

int	check_state(t_lexer *lex, char **line)
{
	t_state	new;

	new = OLD_ST;
	if (**line == '"' && lex->state == D_QUOTE_ST)
		new = ROOT_ST;
	else if (**line == '"' && lex->state == ROOT_ST)
		new = D_QUOTE_ST;
	else if (**line == '\'' && lex->state == S_QUOTE_ST)
		new = ROOT_ST;
	else if (**line == '\'' && lex->state == ROOT_ST)
		new = S_QUOTE_ST;
	else if (**line == '(' && lex->state == ROOT_ST)
		lex->deep++;
	else if (**line == ')' && lex->state == ROOT_ST)
		lex->deep--;
	else if (**line == '*' && lex->state == ROOT_ST && !lex->deep)
		lex->wc = 1;
	if (new)
	{
		lex->state = new;
		if (lex->deep == 0 && (*line)++)
			return (1);
	}
	return (0);
}
