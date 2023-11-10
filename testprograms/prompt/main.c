/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:02:59 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/10 11:12:38 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "sys/wait.h"
#include "unistd.h"
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

void read_command(char *line) {
    //char line[1024];
    int count = 0;
	int c;
	c_purple();
    for (;;) {
        int c = fgetc(stdin);
        line[count++] = (char) c;
        if (c == '\n') 
		{
            break;
        }
    }
}

void type_prompt() {
    static int first_time = 1;
    if (first_time) 
	{
        const char* CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
        write(STDERR_FILENO, CLEAR_SCREEN_ANSI, 12);
        first_time = 0;
    }

    c_red();printf("minihell");c_green();printf(">>");
}

int main() {
    char line[100];

    while(1) 
	{
        type_prompt();
        read_command(line);
		c_cyan(); printf(" LINE |%s|\n", line); c_reset();
    }
	
    return 0;
}