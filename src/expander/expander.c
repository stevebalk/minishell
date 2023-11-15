/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:45:38 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/15 11:35:35 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	check_if_env_variable(t_token *lx, t_list *env)
{
	if ()
}

/* Input should be the lexer struct. It will search
for env varirable metacharacter '$' and will replace
them with there matching env variable, if there is
one, else it will flag them as invalid */
t_token	expander(t_token *lx, t_list *env)
{
	t_token	*head;

	head = lx;
	if (!lx)
		return (NULL);
	while (lx != NULL)
	{
		if (lx->type == TOKEN_WORD)
			
		lx = lx->next;
	}
}