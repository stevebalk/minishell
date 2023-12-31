/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_chunks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:10:48 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/05 10:31:21 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Goes trough every chunk and counts string length. 
Also checks and sets if a least one string exists that 
is not NULL. Returns final_string_length */
static size_t	get_final_str_len(t_ms *ms, int *legit_string)
{
	t_expand	*cur;
	size_t		final_string_len;

	final_string_len = 0;
	cur = ms->exp;
	while (cur)
	{
		if (cur->str != NULL)
			*legit_string = 1;
		final_string_len += ft_strlen(cur->str);
		cur = cur->next;
	}
	return (final_string_len);
}

/* Goes trough every chunk, concatinates the string to
the final string, frees the string inside the chunk, frees
the chunk and at the end sets ms->exp to NULL */
static void	join_final_string(t_ms *ms, char *dst_string)
{
	t_expand	*cur;
	t_expand	*next;

	cur = ms->exp;
	while (cur)
	{
		ft_strlcat(dst_string, cur->str, ft_strlen(cur->str)
			+ ft_strlen(dst_string) + 1);
		next = cur->next;
		if (cur->str)
			free(cur->str);
		free(cur);
		cur = next;
	}
	ms->exp = NULL;
}

/* Joins all chunks to the expanded string and 
frees everything related to this operation */
char	*join_chunks_to_final_word(t_ms *ms)
{
	char		*final_string;
	size_t		final_str_len;
	int			is_legit_str;

	is_legit_str = 0;
	final_str_len = 0;
	final_str_len = get_final_str_len(ms, &is_legit_str);
	if (is_legit_str == 0 && final_str_len == 0)
	{
		free_expander_list(&(ms->exp));
		return (NULL);
	}
	final_string = ft_calloc(final_str_len + 1, sizeof(char));
	check_if_malloc_failed((void *)final_string, ms);
	join_final_string(ms, final_string);
	return (final_string);
}
