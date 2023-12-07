/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:03:32 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/07 13:08:48 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define MAX_LINES 1000


/* TEST FUNCTION DELETE LATER */
void	read_test_file(char **filename, char *test_lines[100])
{
	int		fd;
	char	*line;
	// int		i;

	line = NULL;
	// i = 0;
	fd = open(*filename, O_RDONLY, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(errno);
	}
	line = get_next_line(fd);
	test_lines[0] = line;
	test_lines[0][ft_strlen(test_lines[0]) - 1] = '\0';
	// while (line != NULL && i < MAX_LINES)
	// {
	// 	test_lines[i] = line;
	// 	test_lines[i][ft_strlen(test_lines[i]) - 1] = '\0';
	// 	line = get_next_line(fd);
	// 	i++;
	// }
	close(fd);
}

void	print_lexer_struct(t_token *tk)
{
	while (tk != NULL)
	{
		// printf("prev: %p\n", tk->prev);
		printf("Type: %i\n", tk->type);
		printf("String: %s\n", tk->content);
		// printf("Join: %d\n", tk->join);
		// printf("Cur:  %p\n", tk);
		printf("\n");
		tk = tk->next;
	}
}

const char *tokenTypeNames[] = {
	"WORD",
	"PIPE",
	"REDIRECT",
	"REDIRECT_APPEND",
	"INFILE",
	"HERE_DOC",
	"VARIABLE",
	"EOF"
};

void prettyPrintCmd(t_cmd *cmd) 
{
	int count = 0;
	while (cmd != NULL) {
		c_green(); printf("Command");
		c_red(); printf("  >");
		c_green(); printf(" %i ", count);
		
		c_red(); printf("< \n");
		
		if (cmd->argv != NULL) {
			c_cyan();
			printf("  Arguments:\n");
			char **arg = cmd->argv;
			while (*arg != NULL) {
				c_purple();
				printf("    %s\n", *arg);
				arg++;
			}
		}

		if (cmd->redirs != NULL) {
			c_cyan();
			printf("  Redirections:\n");
			t_redir *redir = cmd->redirs;
			while (redir != NULL) {
				c_blue();
				printf("    Type:");
				c_purple();
				printf(" %s", tokenTypeNames[redir->type]);
				c_blue();
				printf(" Filename: ");
				c_purple();
				printf("%s\n", redir->target);
				c_reset();
				redir = redir->next;
			}
		}
		count++;
		printf("\n");
		cmd = cmd->next;
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	// char	*test_lines[MAX_LINES];
	t_ms	ms;

	init_ms(&ms);
	ms.last_exit_code = "127";

	char teststring[] = "<infile1.txt <infile2.txt wc -l" ;
	lex(teststring, &ms);
	expand(&ms);
	parse(&ms);
	prettyPrintCmd(ms.cmd);
	jexecuter(&ms);
	ms_error(&ms, NULL, 0, 0);
	// free(test_lines[0]);
}

// int main(void)
// {
//     // Example usage
//     printf("%d\n", is_builtin_command("pwd"));  // Should print 1 (true)
//     printf("%d\n", is_builtin_command("ls"));   // Should print 0 (false)
// 	heredoc("ho$la$\"$a\"$$\"b\"");

//     return 0;
// }