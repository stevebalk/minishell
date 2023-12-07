/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:26:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/07 13:25:19 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *tokenTypeNames2[] = {
	"WORD",
	"PIPE",
	"REDIRECT",
	"REDIRECT_APPEND",
	"INFILE",
	"HERE_DOC",
	"VARIABLE",
	"EOF"
};

void	check_infile(t_ms *ms, t_redir *redir)
{
	c_yellow(); printf("check_infile() \n");
	t_redir *tmp_redir;
	int		fd;

	if (!redir)
		return ;

	tmp_redir = redir;	
	
	// open every file and printf error if needed
	while (tmp_redir)
	{
		c_blue();printf("    Type:");c_purple();			printf(" %s", tokenTypeNames2[tmp_redir->type]);
		c_blue();printf(" Filename: ");c_purple();printf("%s\n", tmp_redir->target);c_reset();

		// Check
		fd = open(tmp_redir->target, O_RDONLY, 0644);
		if (fd == -1)
		{
			c_red(); printf("TODO Error Handling Open file in chec_infile \n");
			ms->last_exit_int = 127; 			// richtiger Code?
		}
		else
		{
			ms->last_exit_int = 0; 
		}
			
		close(fd);


		tmp_redir = tmp_redir->next;
	}
	



	c_red(); printf("~check_infile() \n");
}

void	jexecuter(t_ms *ms)
{
	c_yellow(); printf("jexecuter() \n");
	
	t_cmd *tmp_cmd;
	
	if (!ms->cmd)
		return ;

	tmp_cmd = ms->cmd;
	
	while(tmp_cmd)
	{
		check_infile(ms, tmp_cmd->redirs);
		tmp_cmd = tmp_cmd->next;
	}

	
	c_red(); printf("~jexecuter() \n");
}



/*
Jonas Überlegungen

Pro Command:
1x fork

wenn mehr als 1 command --> pipe
pro Pipe braucht mein ein int fd[2] array

alle commands können bzw. müssen hintereinander ablaufen

Executer:
1. zählt die commands
2. zählt die pipes

3. calloc pids für die forks
4. calloc fd[2] für pipe

Schleife für alle Commands
	execute_single(t_command  command);
	
	wenn es einen weiteren command gibt
		--> out FD in den nächsten in FD schreiben


*/