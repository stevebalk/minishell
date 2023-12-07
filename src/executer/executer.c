/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:26:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/07 20:20:07 by jonas            ###   ########.fr       */
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
		if (tmp_redir->type == TOKEN_REDIRECT || tmp_redir->type ==TOKEN_INFILE)
		{
			fd = open(tmp_redir->target, O_RDONLY, 0644);
			printf("\t  open file >%s< \n", tmp_redir->target);
			if (fd == -1)
			{
				c_red(); printf("\t\tError 1 --> TODO Error Handling Open file in check_infile \n"); c_reset();
				ms->last_exit_code_int = 1; 			// richtiger Code?
			}
			else
			{
				c_green(); printf("\t\tFD: %i   --> TODO Error Handling Open file in check_infile \n", fd); c_reset();
				ms->last_exit_code_int = 0; 
			}
				
			close(fd);
		}
		tmp_redir = tmp_redir->next;
	}
	



	c_red(); printf("~check_infile() \n");
}
int		get_len_cmd(t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	int		count;

	tmp_cmd = cmd;
	count = 0;
	while (tmp_cmd)
	{
		tmp_cmd = tmp_cmd->next;
		count++;
	}
	
	return (count);
}

char	*get_last_redir(t_redir *redir, unsigned int type)
{
	t_redir	*tmp_redir;
	int		count;
	char	*last_redir;
	int		last_type;
	
	last_type = -1;
	last_redir = NULL;
	tmp_redir = redir;
	count = 0;
	while (tmp_redir)
	{
		if (tmp_redir->type == type)
		{
			last_redir = tmp_redir->target;
			last_type = tmp_redir->type;
			count++;
		}
		tmp_redir = tmp_redir->next;
	}
	printf("---\n");
	c_yellow(); printf("get_last_redir ");
	c_blue(); printf("nr: ");
	
	c_purple(); printf("%i ", count);

	printf("    type nr: %i   ", last_type);
	fflush(stdout);
				
	c_blue(); printf("type: ");
	c_purple(); printf("%s ", tokenTypeNames2[last_type]);
	c_blue(); printf("redir: ");
	fflush(stdout);

	c_purple(); printf("%s \n", last_redir);


	return (last_redir);
}

void print_int_array(int **arr)
{
	int i;
	int i2;
	c_yellow(); printf("print_int_array() \n"); c_reset();

	i = -1;
	while(i++, arr[i])
	{
		i2 = -1;
		while(i2++, arr[i][i2])
			printf("arr[%i][%i] == %i\n", i, i2, arr[i][i2]);

	}
}

void	jexecuter(t_ms *ms)
{
	c_yellow(); printf("jexecuter() \n");
	
	t_cmd *tmp_cmd;
	
	if (!ms->cmd)
		return ;

	tmp_cmd = ms->cmd;
	
	// check files
	while(tmp_cmd)
	{
		check_infile(ms, tmp_cmd->redirs);
		tmp_cmd = tmp_cmd->next;
	}
	c_cyan(); printf("Last Exit Code: "); c_reset(); printf("%i \n", ms->last_exit_code_int);

	// Count Commands
	int command_count = get_len_cmd(ms->cmd);
	c_cyan(); printf("count: "); c_reset(); printf("%i \n", command_count);

	
	//get the last infile of 
	tmp_cmd = ms->cmd;
	while (tmp_cmd)
	{
		char *last_infile = get_last_redir(tmp_cmd->redirs, TOKEN_INFILE);
		char *last_redirect = get_last_redir(tmp_cmd->redirs, TOKEN_REDIRECT);
		c_blue(); printf("Last Infile: "); 
		c_purple(); printf("%s\n", last_infile); 
		
		c_blue(); printf("Last Redirec: ");
		c_purple(); printf("%s\n", last_redirect); 

		
		tmp_cmd = tmp_cmd->next;
	}
	
	printf("size of FD[2]: %i \n", (int)sizeof(int[2]));

	// mallocs FD[2] for the commands
	int **FD;
	int i;
	FD = NULL;
	i = -1;
	FD = ft_calloc((command_count + 1), sizeof(int *));

	while(i++, i < command_count)
	{
		printf("%i \n", i);
		FD[i] = ft_calloc(1, sizeof(int[2]));
	}
	
	FD[i + 1] = NULL;
	FD[0][0] = 11;
	FD[0][1] = 22;
	FD[1][0] = 44;
	FD[1][1] = 55;
	print_int_array(FD);
	
	//printf("command count: %i      sizeof FD Array: %i \n", command_count, (int)sizeof(FD));
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