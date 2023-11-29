/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:25:47 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/28 16:27:26 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ms(t_ms *ms)
{
	ms->cmd = NULL;
	ms->envp = NULL;
	ms->exp = NULL;
	ms->last_exit_code = NULL;
	ms->tk = NULL;
	ms->unexpected_token = NULL;
}