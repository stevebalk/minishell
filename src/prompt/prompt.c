/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:16:37 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/03 13:56:29 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/main.h"
#include "../../include/minishell.h"
#include "../include/builtins.h"

/* DEBUG DELETE LATER */
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

// copy from steves main after first merge
void quick_lexer(t_ms *ms, char *prompt_in)	
{
	// ACHTUNG Hier sind noch memory leaks!!! 
	//t_ms	ms;
	c_yellow(); printf("quick_lexer() >"); 
	c_green(); printf("%s", prompt_in);
	c_yellow(); printf("<\n"); c_reset();

	//init_ms(ms);
	ms->last_exit_code = 127;
	lex(prompt_in, ms); // Hier den String angeben der getestet werden soll
	c_yellow(); printf("DEBUG before expand\n"); c_blue();
	
	print_lexer_struct(ms->tk); // DEBUG before expand
	expand(ms);
	
	c_yellow(); printf("DEBUG after expand\n"); c_blue();
	
	print_lexer_struct(ms->tk); // DEBUG after expand
	
	c_reset();
	//free_ms(&ms);
}

void	prompt_handler(t_ms *ms)
//void	prompt_handler(t_list **history_lst, t_list **env_llst, t_list **env_llst_sorted)
{
	char	*prompt_in;
	int		count;
	// int		hit_sig;

	(void)count;
	count = 0;
	prompt_in = NULL;
	// hit_sig = 0;
	if (CLR_SCREEN == 1)
		clear_screen();
	while (1)
	{
		// rl_clear_history();
		if (LOGO_ABOVE_PROMPT == 1)
			intro3();
		prompt_in = readline("\033[0;35mmini(s)hell\033[0;33m >> \033[0;36m");

		tty_set_flag(TTY_OMIT_LF, 0);

		// if (prompt_in != NULL || hit_sig == 0)
		if (prompt_in != NULL)
		{
			// hit_sig = 1;
			if (ft_strlen(prompt_in) > 0)
			{
				clear_history();
				add_variable_to_llst(&ms->hist_llst, prompt_in);
				lex(prompt_in, ms);
				expand(ms);
				parse(ms);
				executer(ms);
				limit_history_llst(&ms->hist_llst);
				write_history_llst(ms->tmp_history_folder_file, &ms->hist_llst);
				add_history_llst_to_prompt(&ms->hist_llst);
				//add_history(prompt_in);
				free_n_null((void **)&prompt_in);
			}
			else
				free_n_null((void **)&prompt_in);
		}
		else
		{
			//rl_replace_line("\033[0;35mmini(s)hell\033[0;33m >> \033[0;36mExit", 0);
			//rl_replace_line("Exit", 1);
			//rl_on_new_line();
			//prompt_in = readline("\033[0;35mmini(s)hell\033[0;33m >> \033[0;36mexit\n");

			//rl_redisplay();
			//printf("\033[0;35mmini(s)hell\033[0;33m >> \033[0;36mExit");
			//printf("\nprompt_in == NULL\n");
			// hit_sig = 1;
			// printf("sig == 2 \n");c_red(); 
			free_n_null((void **)&prompt_in);
			// printf("exit\n");
			c_red();
			write(STDERR_FILENO, "exit\n", 5);

			break ;
		}
		count++;
	}
	//c_red();
	//printf("~prompt Handler()\n");
}

/*
BASH
	Control + C		--> Closes the actual process and returns to BASH
	Control + D		--> types exit (without ^D) and closes BASH
*/