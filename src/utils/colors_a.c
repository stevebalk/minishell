/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:14:39 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/10 12:08:57 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	c_red(void)
{
	printf("\033[0;31m");
}

void	c_green(void)
{
	printf("\033[0;32m");
}

void	c_blue(void)
{
	printf("\033[0;34m");
}

void	c_purple(void)
{
	printf("\033[0;35m");
}

void	c_yellow(void)
{
	printf("\033[0;33m");
}