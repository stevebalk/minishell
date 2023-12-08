/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:54:43 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/05 19:38:27 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_command(char *str)
{
	size_t	i;
	char	*built_ins[8];

	built_ins[0] = "echo";
	built_ins[1] = "cd";
	built_ins[2] = "pwd";
	built_ins[3] = "export";
	built_ins[4] = "unset";
	built_ins[5] = "env";
	built_ins[6] = "exit";
	built_ins[7] = NULL;
	i = 0;
	while (built_ins[i] != NULL)
	{
		if (ft_strncmp(built_ins[i], str, ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return (0);
}