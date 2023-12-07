/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:02:49 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/07 13:06:39 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include "libft.h"
# include "lexer.h"
# include "expander.h"
# include "parser.h"
# include "executer.h"

/*
⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣶⣤⡀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⡄⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⡿⠁⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣦⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⡀⠀⠀⠀
⠀⠀⠀⠀⢠⣿⣿⣿⣿⡿⣿⣿⣧⣀⠀⠀
⠀⠀⠀⠀⢺⣿⣿⣿⣿⣧⣬⣻⢿⣿⣿⡦
⠀⠀⠀⠀⠀⠙⠻⠿⢿⣿⣿⣿⣿⡏⠛⠁
⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⣽⣿⡿⠁⠀⠀
⠀⢀⡠⣿⣷⣤⡀⠀⠀⢸⣿⣿⠃⠀⠀⠀
⠰⠿⠿⠿⠿⠿⠇⠀⠠⠿⠿⠏
Minishell
*/

/* Main Minishell struct */
typedef struct s_ms
{
	t_token		*tk;
	t_cmd		*cmd;
	t_list		*envp;
	t_expand	*exp;
	char		*last_exit_code;
	char		*unexpected_token;
}				t_ms;

/* Init */
void		init_ms(t_ms *ms);

/* lexer */
void		lex(char *str, t_ms *ms);
t_token		*create_token(t_ms *ms);
t_token		*get_last_token(t_token *lx);
t_token		*token_list_append(t_ms *ms);
int			set_word_token(char *str, t_token *token, t_ms *ms);
int			set_special_token(char *str, t_token *token, t_ms *ms);

/* EXPANDER */

void		expand(t_ms *ms);
void		check_if_valid_quote_count(t_token *token, t_ms *ms);
t_expand	*create_expand_node(t_ms *ms);
t_expand	*append_chunk(t_ms *ms);
void		append_and_fill_chunk_with_str(t_ms *ms, const char *src,
				size_t len);
void		expand_env_varible(char **str, t_ms *ms, char *prev_quote);
void		append_and_fill_chunk_with_str(t_ms *ms, const char *src,
				size_t len);
void		expand_no_quotes(char **str, t_ms *ms, char *quote);
void		expand_single_quote_content(char **str, t_ms *ms);
void		expand_double_quote_content(char **str, t_ms *ms,
				char *prev_quote);
char		*join_chunks_to_final_word(t_ms *ms);
void		create_empty_string_chunk(t_ms *ms);

/* PARSER */
int			parse(t_ms *ms);
t_cmd		*create_cmd_node(t_ms *ms);
t_cmd		*append_cmd_node(t_ms *ms);
t_redir		*append_redir_node(t_ms *ms, t_cmd *cmd);
t_redir		*create_heredoc_only_redir(t_redir *list);
int			unexpected_token(t_ms *ms, char *token_name, int shall_free);

/* EXECUTER */
int			is_builtin_command(char *str);
void		heredoc(char *delimiter);

void	jexecuter(t_ms *ms);

/* Error handling */

void		check_if_malloc_failed(void *src, t_ms *ms);
void		ms_error(t_ms *ms, char *msg, int shall_exit, int use_errno);

/* Freeing stuff */
void		free_ms(t_ms *ms);
void		free_token(t_token **token);
void		free_token_but_not_content(t_token **token);
void		free_token_list(t_token **token);

void		free_expander_list(t_expand **list);

void		free_cmd_list(t_cmd **cmd);
void		free_cmd_list_exept_here_doc(t_cmd **cmd);
void		free_redir_node(t_redir **node);
void		free_redir_list(t_redir **list);

// del 
void	c_red(void);
void	c_green(void);
void	c_blue(void);
void	c_purple(void);
void	c_yellow(void);
void	c_cyan(void);
void	clear_screen(void);
void	c_reset(void);

#endif