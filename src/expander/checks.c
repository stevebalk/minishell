/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:14:53 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/24 17:25:11 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns TRUE if ' or " */
size_t	is_quote(const char *str)
{
	if (ft_strchr(QUOTE, *str) == NULL)
		return (0);
	return (1);
}

/* Returns TRUE if ' */
size_t	is_single_quote(const char *str)
{
	if (*str == '\'')
		return (1);
	return (0);
}

/* Returns TRUE if " */
size_t	is_double_quote(const char *str)
{
	if (*str == '\"')
		return (1);
	return (0);
}

/* Returns TRUE if "$" */
size_t	is_env_variable(const char *str)
{
	if (*str == '$')
		return (1);
	return (0);
}

/* Checks if any quote has a closing quote */
void	check_if_valid_quote_count(t_token *token, t_ms *ms)
{
	char	*str;
	char	quote;

	quote = 0;
	str = token->content;
	while (*str != '\0')
	{
		if ((*str == '\'' || *str == '\"') && quote == 0)
			quote = *str;
		else if (*str == quote)
			quote = 0;
		str++;
	}
	if (quote != 0)
		ms_error(ms, "Wrong number of quotes", 1, 0);
}