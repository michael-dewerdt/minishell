/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:09:25 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/24 08:25:06 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_arguments(t_token *tok);
static t_token	*parse_cmd(t_datas *datas, t_token *tok, t_command *cmd);

t_command	*parser(t_datas *datas, t_token *tok, t_command *prev)
{
	t_command	*cmd;
	int			lex_succ;

	lex_succ = ((tok && 1) || 0);
	cmd = ft_calloc(1, sizeof(*cmd));
	if (prev)
		cmd->prev = prev;
	cmd->argv = ft_calloc(count_arguments(tok) + 1, sizeof(char *));
	cmd->argc = 0;
	while (tok && tok->type < PIPE)
		tok = parse_cmd(datas, tok, cmd);
	if (tok)
	{
		if (tok->next)
			cmd->ope = tok->type;
		cmd->next = parser(datas, tok->next, cmd);
		free(tok->value);
		free(tok);
	}
	if (!lex_succ)
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

static size_t	count_arguments(t_token *tok)
{
	size_t	ret;

	ret = 0;
	while (tok && tok->type < PIPE)
	{
		if (tok->type == WORD)
			ret++;
		if (tok->value[0] == '(')
			ret += 2;
		tok = tok->next;
	}
	return (ret);
}

static void		update_redir(t_datas *datas, t_command *cmd, t_token *tok);

static t_token	*parse_cmd(t_datas *datas, t_token *tok, t_command *cmd)
{	
	t_token		*prev_tok;

	if (tok->value[0] == '(')
	{
		cmd->argv[cmd->argc++] = get_var_value(datas, "MINISH", 7);
		cmd->argv[cmd->argc++] = ft_strdup("-c");
		cmd->argv[cmd->argc++] = ft_substr(tok->value,
				1, ft_strlen(tok->value) - 2);
	}
	else if (tok->type)
		update_redir(datas, cmd, tok);
	else
		cmd->argv[cmd->argc++] = ft_strdup(tok->value);
	prev_tok = tok;
	tok = tok->next;
	free(prev_tok->value);
	free(prev_tok);
	return (tok);
}

static int	push_heredoc(t_datas *datas, char *str)
{
	char	*line;
	int		pip[2];

	pipe(pip);
	while (1)
	{
		line = readline(">");
		if (!ft_strncmp(line, str, ft_strlen(str) + 1))
			break ;
		ft_putstr_fd(expend_str(datas, line), pip[1]);
		write(pip[1], "\n", 1);
	}
	close(pip[1]);
	return (pip[0]);
}

static void	update_redir(t_datas *datas, t_command *cmd, t_token *tok)
{
	if (tok->type == OUT)
	{
		if (cmd->fd[1])
			close(cmd->fd[1]);
		cmd->fd[1] = open(tok->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	else if (tok->type == ADD)
	{	
		if (cmd->fd[1])
			close(cmd->fd[1]);
		cmd->fd[1] = open(tok->value, O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	else if (tok->type == IN)
	{	
		if (cmd->fd[0])
			close(cmd->fd[0]);
		cmd->fd[0] = open(tok->value, O_RDONLY);
	}
	else if (tok->type == HD)
	{
		if (cmd->fd[0])
			close(cmd->fd[0]);
		cmd->fd[0] = push_heredoc(datas, tok->value);
	}
}
