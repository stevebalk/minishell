/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:15:34 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/04 14:06:27 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// check every Path in PATH Array with program name; returns a valid path or NULL
char *check_program_with_path(t_ms *ms, char *prog_name)
{
	char	*tmp_prog;
	int		i;
	
	c_yellow(); printf("check_program_with_path()  >"); c_green(); printf("%s", prog_name); 
	c_yellow(); printf("<\n"); c_reset();

	i = -1;
	while (ms->path_arr[++i])
	{
		tmp_prog = join_three_string(ms->path_arr[i], "/", prog_name);
		c_cyan(); printf("i: %i   >%s< \n", i, tmp_prog);
		if (!access(tmp_prog, F_OK))
			return (tmp_prog);
		else
		{
			if (tmp_prog)
				free(tmp_prog);
			tmp_prog = NULL;
		}
	}
	
	c_red(); printf("~check_program_with_path()  >"); c_green(); printf("%s", tmp_prog); 
	c_red(); printf("<\n"); c_reset();
	return (NULL);
}