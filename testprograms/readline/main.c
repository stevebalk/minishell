/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:48:54 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/10 10:58:31 by jopeters         ###   ########.fr       */
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

void    clear_screen(void)
{
    printf("\e[1;1H\e[2J");
}

void	c_reset(void)
{
	printf("\033[0m");
}

char *prompt(char *in)
{
    c_red();printf("minihell");
    c_yellow();printf(">>");
        
    c_cyan();
    in = readline("");
        
    c_green();
    printf("|%s|\n", in);

    return in;  
}

int main(void)
{
    char *prompt_in;

    clear_screen();

    while(1)
    {
        prompt_in = prompt(prompt_in);
        free(prompt_in);
    }
    
    return 0;
}


/*

gcc main.c -lreadline

*/