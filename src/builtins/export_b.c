/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:22:34 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/21 16:16:38 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

// returns 1 if c is alpha or _
int check_first_c(char c)
{
	if (ft_isalpha(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

// returns 1 if c is alpha, _ or digit
int check_other_c(char c)
{
	if (ft_isalpha(c))
		return (1);
	if (ft_isdigit(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

// return 1 if var name is valid; checks only till =
int	check_var_name(char *str)
{
	int	i;

	i = -1;
	while (i++, str[i] && str[i] != '=')
	{
		if (i == 0 && !check_first_c(str[i]))
			return (0);
		if (i > 0 && !check_other_c(str[i]))
			return (0);
	}
	return (1);
}