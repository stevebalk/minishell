/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:03:32 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/11 16:26:46 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/minishell.h"
#include "minishell.h"

/* DEBUG DELETE LATER */
/*
void	print_lexer_struct(t_token *tk)
{
	while (tk != NULL)
	{
		printf("Type: %i\n", tk->type);
		printf("String: %s\n", tk->content);
		printf("\n");
		tk = tk->next;
	}
}

void test(t_ms *ms)
{
	(void)ms;
//    printf("PATH : %s\n", getenv("PATH"));
//    printf("HOME : %s\n", getenv("HOME"));
//    printf("ROOT : %s\n", getenv("ROOT"));
//    printf("PWD  : %s\n", getenv("PWD"));

	char *tmp = check_program_with_path(ms, "ls");
	printf("checked prog: %s \n", tmp);
	free(tmp);
}
*/




void ini_env_history_etc(t_ms *ms, char **env)
{
	load_env_to_llst(&ms->env_llst, env);
	copy_env_home_to_ms_struct(ms);
	copy_path_to_ms_ms_struct(ms);
	copy_llst(&ms->env_llst, &ms->env_llst_sorted);
	sort_list(ms->env_llst_sorted);
	history_master(&ms->hist_llst);
	add_shell_level(&ms->env_llst, &ms->env_llst_sorted);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_ms	ms;
// 	c_yellow(); printf("*** main () ***\n"); c_reset();
// 	init_ms(&ms);
// 	(void)argc;
// 	(void)argv;
// 	(void)env;

// 	if (!LOGO_ABOVE_PROMPT)
// 		intro3();
	
// 	ini_env_history_etc(&ms, env);

// 	prompt_handler(&ms);
	
	
// 	free_ms(&ms);
	
// 	c_red();
// 	printf("*** ~main () ***\n"); c_reset();
// 	return (EXIT_SUCCESS);
// }

/* ---------- INPUT TEST MAIN ------------- */


void prettyPrintCmd(t_cmd *cmd) 
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

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	t_ms	ms;
	//char teststring[] = "> outfile.txt << infile.txt  | < dsd | fdfs>fdsf | fdsf < fdf fggre >f fd | fdsf" ;
	char teststring[] = "> outfile.txt > outX.txt <infile.txt /usr/bin/wc -l" ;
	printf("teststring >%s<\n", teststring);
	init_ms(&ms);
	ini_env_history_etc(&ms, env);
	lex(teststring, &ms);
	expand(&ms);
	parse(&ms);
	//ms.extern_env = env;
	//show_env_arr(ms.extern_env);
	prettyPrintCmd(ms.cmd);
	jexecuter(&ms, env);
	printf("~\n");

	//free_ms(&ms);
}

//<inX <infile.txt >outX >outfile.txt wc -l
//>outX >outfile.txt <inX <infile.txt wc -l

// int	main(int argc, char **argv)
// {
// 	// char	*test_lines[MAX_LINES];
// 	t_ms	ms;

// 	init_ms(&ms);
// 	ms.last_exit_code = "127";
// 	if (argc == 2)
// 	{
// 		if (access(argv[1], F_OK) == 0)
// 			// read_test_file(argv + 1, test_lines);
// 			printf("OK\n");
// 		else
// 		{
// 			perror("File doesn't exist");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else
// 	{
// 		printf("Wrong input. Use: ./lexer <test_file>\n");
// 		printf("Testfile should be filled with bash commands\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	char teststring[] = "> dsads << infile | < dsd | fdfs>fdsf | fdsf < fdf fggre >f fd | fdsf" ;
// 	lex(teststring, &ms);
// 	expand(&ms);
// 	parse(&ms);
// 	prettyPrintCmd(ms.cmd);
// 	ms_error(&ms, NULL, 0, 0);
// 	// free(test_lines[0]);
// }

// int	main(void)
// {
// 	t_ms	ms;

// 	init_ms(&ms);
// 	ms.last_exit_code = ft_strdup("127");
// 	char teststring[] = "> dsads << infile | < dsd | fdfs>fdsf | fdsf < fdf fggre >f fd | fdsf" ;
// 	lex(teststring, &ms);
// 	expand(&ms);
// 	parse(&ms);
// 	heredoc("'ff'", &ms);
// 	// prettyPrintCmd(ms.cmd);
// 	free_ms(&ms);
// }

// int main(void)
// {
//     // Example usage
//     printf("%d\n", is_builtin_command("pwd"));  // Should print 1 (true)
//     printf("%d\n", is_builtin_command("ls"));   // Should print 0 (false)
// 	heredoc("ho$la$\"$a\"$$\"b\"");

//     return 0;
// }

