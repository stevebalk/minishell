/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:48:54 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/10 10:39:48 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

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

void	c_cyan(void)
{
	printf("\033[0;36m");
}

void	c_reset(void)
{
	printf("\033[0m");
}


int main(void)
{
    char *input;
    printf("\e[1;1H\e[2J");
    while(1)
    {
        c_red();printf("minihell");
        c_yellow();printf(">>");
        
        c_cyan();
        input = readline("");
        
        c_green();
        printf("|%s|\n", input);
    }
    
    free(input);
    return 0;
}


/*

gcc main.c -lreadline

*/