/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_strings_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:48:52 by jonas             #+#    #+#             */
/*   Updated: 2024/01/04 17:04:09 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

// add str1 + str2 + str3; you have to free memory later
char	*join_three_string(char *str1, char *str2, char *str3)
{
	char	*new_str;
	int		len[3];

	len[0] = ft_strlen(str1);
	len[1] = ft_strlen(str2);
	len[2] = ft_strlen(str3);
	new_str = (char *)ft_calloc((len[0] + len[1] + len[2] + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcat(new_str, str1, len[0] + 1);
	ft_strlcat(new_str, str2, ft_strlen(new_str) + len[1] + 1);
	ft_strlcat(new_str, str3, ft_strlen(new_str) + len[2] + 1);
	return (new_str);
}

static	int	count_symbol(char *str, char symbol)
{
	int		count;
	int		i;

	i = -1;
	count = 0;
	while (i++, str[i])
	{
		if (str[i] == symbol)
			count++;
	}
	return (count);
}

// returns a string witout given symbols
char	*get_string_without_symbols(char *str_in, char symbol)
{
	int		count;
	int		i;
	int		i2;
	char	*new_str;

	if (!str_in)
		return (NULL);
	count = count_symbol(str_in, symbol);
	new_str = (char *)malloc(sizeof(char)
			*((int)ft_strlen(str_in) - count + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	i2 = 0;
	while (str_in[i])
	{
		if (str_in[i] != symbol)
			new_str[i2++] = str_in[i];
		i++;
	}
	new_str[i2] = '\0';
	return (new_str);
}