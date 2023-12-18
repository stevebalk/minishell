/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:25:47 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/18 16:20:11 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ms(t_ms *ms)
{
	ms->tk = NULL;
	ms->exp = NULL;
	ms->cmd = NULL;
	ms->cmd_io = NULL;
	ms->fd_stdin = STDIN_FILENO;
	ms->fd_stdout = STDOUT_FILENO;
	ms->last_exit_code = 0;
	ms->unexpected_token = NULL;

	ms->envp = NULL;
	ms->home_dir = NULL;
	ms->path_arr = NULL;

	ms->env_llst = NULL;
	ms->env_llst_sorted = NULL;
	ms->hist_llst = NULL;
}
