/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:50:44 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/27 08:51:16 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define ENVP_MAX_SIZE  4096
# define STR_MAX_SIZE 4096
# define PATHS_MAX_SIZE 126
# define DEBUG 1

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <termios.h>
# include <dirent.h>

typedef struct s_command
{
	pid_t				pid;
	char				**argv;
	int					argc;
	int					ope;
	int					fd[2];
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_datas
{
	char				**envp;
	int					exit_code;
	int					silent;
}	t_datas;

void		free_cmd(t_command *cmd);

// ---------------------------------- Utils.c
int			is_empty(char *line);
int			handle_status(t_datas *datas, int status);
void		nothing(int sig_num);
void		sigs_handler(int sig_num);
void		halt(t_datas *datas, int ret_code, int silent);

// ---------------------------------- Errors.c
int			cmd_error(char *cmd, char *msg, char *msg2);
int			is_valid_identifier(char *ident, int silent);

// ----------------------------------Builtins.c
int			is_builtin(char *cmd);
int			ft_echo(t_command *cmd);
int			ft_pwd(t_command *cmd);
int			ft_cd(t_datas *datas, t_command *cmd);
int			ft_exit(t_datas *datas, t_command *cmd);

// ----------------------------------Env.c
int			ft_unset(t_datas *datas, t_command *cmd);
int			ft_env(t_datas *datas, t_command *cmd, int declared_pop);
int			ft_export(t_datas *datas, t_command *cmd);

// ----------------------------------Caller.c
int			call_builtin(t_datas *datas, t_command *cmd);
int			caller(t_datas *datas, t_command *cmd);

// ----------------------------------Parser.c
typedef enum e_type
{
	WORD,
	OUT,
	ADD,
	IN,
	HD,
	PIPE,
	AND,
	OR,
}			t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
}	t_token;

t_command	*parser(t_datas *datas, t_token *tok, t_command *prev);

// ----------------------------------Lexer.c
typedef enum e_state
{
	OLD_ST,
	ROOT_ST,
	S_QUOTE_ST,
	D_QUOTE_ST,
}		t_state;

typedef struct s_lex
{
	t_state		state;
	t_type		type;
	t_type		next_type;
	t_token		*tokens;
	int			wc;
	int			deep;
	int			n_elem;
	int			empty;
}		t_lexer;

t_token		*lexer(t_datas *datas, char *line);
int			create_token(t_lexer *lex, char str[]);

char		*get_var_value(t_datas *datas, char *line, int name_len);
int			check_state(t_lexer *lex, char **line);
char		*expend_str(t_datas *datas, char *line);
int			replace_var(t_datas *datas, char **line, char *tmp, int tmp_i);
int			set_redir(t_lexer *lex, char **line, char ch);

int			create_wc(t_lexer *lex, char *wc);

#endif
