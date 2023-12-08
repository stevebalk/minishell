/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:10:30 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/08 13:14:40 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* Redirection struct, used by t_cmd to save
redirections in a linked list*/
typedef struct s_redir
{
	t_token_type	type;			// JJJ warum nicht t_token_type ?
	char			*target;
	struct s_redir	*next;
}				t_redir;

/* Parser struct, saves all redirections
and commands */
typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}				t_cmd;

#endif