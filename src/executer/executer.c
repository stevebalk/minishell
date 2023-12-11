/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:26:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/11 15:43:58 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_file(t_ms *ms, t_redir *redir)
{
	char *tokenTypeNames[] = {
		"WORD",
		"PIPE",
		"REDIRECT",
		"REDIRECT_APPEND",
		"INFILE",
		"HERE_DOC",
		"VARIABLE",
		"EOF"
	};
	c_yellow(); printf("check_file() \n");
	t_redir *tmp_redir;
	int		fd;

	if (!redir)
		return ;

	tmp_redir = redir;	
	
	// open every file and printf error if needed
	while (tmp_redir)
	{
		c_blue();printf("    Type:");c_purple();			printf(" %s", tokenTypeNames[tmp_redir->type]);
		c_blue();printf(" Filename: ");c_purple();printf("%s\n", tmp_redir->target);c_reset();

		// Check Infile
		if (tmp_redir->type == TOKEN_INFILE)
		{
			fd = open(tmp_redir->target, O_RDONLY, 0644);
			printf("\t  open IN file >%s< \n", tmp_redir->target);
			if (fd == -1)
			{
				c_red(); printf("\t\tError 1 --> TODO Error Handling Open in file in check_file \nCancel EXECUTION\n\n"); c_reset();
				ms->last_exit_code_int = 1; 			// richtiger Code?
			}
			else
			{
				c_green(); printf("\t\tFD: %i   --> TODO Error Handling Open in file in check_file \n", fd); c_reset();
				ms->last_exit_code_int = 0; 
			}
				
			close(fd);
		}
		// Check Outfile
		if (tmp_redir->type == TOKEN_REDIRECT)
		{
			fd = open(tmp_redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			printf("\t  open OUT file >%s< \n", tmp_redir->target);
			if (fd == -1)
			{
				c_red(); printf("\t\tError 1 --> TODO Error Handling Open OUT file in check_file\n"); c_reset();
				ms->last_exit_code_int = 1; 			// richtiger Code?
			}
			else
			{
				c_green(); printf("\t\tFD: %i   --> TODO Error Handling Open file in check_file \n", fd); c_reset();
				ms->last_exit_code_int = 0; 
			}
				
			close(fd);
		}
		tmp_redir = tmp_redir->next;
	}
	



	c_red(); printf("~check_file() \n");
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
	char *tokenTypeNames[] = {
		"WORD",
		"PIPE",
		"REDIRECT",
		"REDIRECT_APPEND",
		"INFILE",
		"HERE_DOC",
		"VARIABLE",
		"EOF"
	};
	
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
	c_purple(); printf("%s ", tokenTypeNames[last_type]);
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

void	jexecuter(t_ms *ms, char **env)
{
	c_yellow(); printf("jexecuter() \n");
	
	t_cmd *tmp_cmd;
	
	if (!ms->cmd)
		return ;

	tmp_cmd = ms->cmd;		// Command list auf Anfang setzen
	// check files
	while(tmp_cmd)
	{
		check_file(ms, tmp_cmd->redirs);
		tmp_cmd = tmp_cmd->next;
	}
	c_cyan(); printf("Last Exit Code: "); c_reset(); printf("%i \n", ms->last_exit_code_int);

	// Count Commands
	int command_count = get_len_cmd(ms->cmd);
	c_cyan(); printf("Command count: "); c_reset(); printf("%i \n", command_count);

	
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
	
	// FD[i + 1] = NULL;
	// FD[0][0] = 11;
	// FD[0][1] = 22;
	// FD[1][0] = 44;
	// FD[1][1] = 55;
	print_int_array(FD);


	// from J_pipex   start_pipe
	int command_i;
	command_i = 0;
	//pid_t pid;
	tmp_cmd = ms->cmd;
	while (command_i < command_count && tmp_cmd)
	{
		// if (pipe(FD[command_i]) == -1)
		// {
		// 	c_red(); printf("error PIPE() \n"); c_reset(); 
		// }
		// pid = fork();
		// if (pid == -1)
		// {
		// 	c_red(); printf("error pid = fork() \n"); c_reset(); 
		// }
		// if (!pid)
		{
		//child(var, fds, environment);
		//		|
		//		|
		//		V
		// child()
			int		fd;
			
			if (tmp_cmd->argv[0] == NULL)
				return ;
			if (dup2(FD[command_i][1], STDOUT_FILENO) == -1)
				printf( "error dup2 (out): child:\n");
			char *last_infile_ = get_last_redir(tmp_cmd->redirs, TOKEN_INFILE);
			printf(">> last INFILE: %s \n", last_infile_);
			fd = open(last_infile_, O_RDONLY, 0644);
			if (fd == -1)
				printf("error input: \n");
			if (dup2(fd, STDIN_FILENO) == -1)
				printf("dup2 (in): child:\n");
			close(fd);
			close(FD[command_i][0]);
			char *newPath = check_program_with_path(ms, tmp_cmd->argv[0]);
			printf("newPath >%s< \n", newPath);
			int exc = execve(newPath, tmp_cmd->argv, env);
			
			if (exc == -1)
			{ 
				printf("child: execve\n");
			}
			else
			{
				printf(" exc: %i \n", exc);
			}
			printf("end of command: %i \n", command_i);
		}
		command_i++;
	}
	


	
	
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