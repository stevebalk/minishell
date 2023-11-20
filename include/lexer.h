/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:01:28 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/20 16:16:57 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// Enum for token types
/*
WORD			= "ALNUM STRING" or "/" or "."
PIPE			= |
REDIRECT		= >
REDIRECT_APPEND	= >>
INFILE			= <
HERE_DOC		= <<
TOKEN_EOF		= NULL
*/
typedef	enum
{
	TOKEN_WORD				= 0,
	TOKEN_PIPE				= 1,
	TOKEN_REDIRECT			= 2,
	TOKEN_REDIRECT_APPEND	= 3,
	TOKEN_INFILE			= 4,
	TOKEN_HERE_DOC			= 5,
	TOKEN_VARIABLE			= 6,
	TOKEN_EOF				= 7
}		e_token_type;

# define TOKEN_TYPES	"|<>"

/* Token struct, created by the lexer to
store the tokens used by the parser.

Doubly linked list
type		= Which token type (WORD, PIPE, REDIRECT ...)
content		= String for the specific token
join		= Should the content joined with the next token?
*/
typedef struct	s_token
{
	e_token_type	type;
	char			*content;
	int				join;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

/* Lexer */


t_token		*create_token(t_token *tk_head);
int			set_special_token(char *str, t_token *token, t_token *tk_head);
int			set_word_token(char *str, t_token *token, t_token *tk_head);
int			set_word_quote_token(char *str, t_token *token, t_token *tk_head);
t_token		*lexer(char *str);
t_token		*get_last_token(t_token *lx);

#endif
