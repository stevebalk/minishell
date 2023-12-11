/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:56:23 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/11 12:28:32 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdio.h>
# include <stdlib.h>
// # include <readline/readline.h>
// # include <readline/history.h>
# include "../libs/readline/include/readline/readline.h"
# include "../libs/readline/include/readline/history.h"

# include "../libs/libft/include/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
// # include "struct.h"

#define FILE_HISTORY "history.txt"
#define MAX_HISTORY 10
#define CLR_SCREEN 0
#define LOGO_ABOVE_PROMPT 0
//debug
//#define PRINT_DEALLOC

// contains, the copy of a  export var like >a="huhu"<; the var_name >a<,
// the raw value >"huhu"< the value witout quotes >huhu<
// and the value with quotes >"huhu"<
// self value, can and have to be used manually
typedef struct s_var_names
{
	char	*raw_copy;
	char	*var_name;
	char	*raw_value;
	char	*value_without_quotes;
	char	*value_added_quotes;
	int		has_equal;
	int		self_value;
}	t_var_names;


int		main(int argc, char **argv, char **env);

// Prompt
//void	prompt_handler(t_ms *ms);

// prompt/signal
void	handle_sigint(int sig);

// builtin
// echo
void	builtin_echo(char **str_arr, int n_flag);
void	test_parser_echo(t_list **env_llst, t_list **env_llst_sorted,
			char *str);

// env
void	show_env_arr(char **env);
void	load_env_to_llst(t_list **env_lst, char **env);
void	show_env_llist(t_list **lst);
void	add_variable_to_llst(t_list **llst, char *var);
void	add_shell_level(t_list **env_llst, t_list **env_llst_sorted);

// export
void	export_arg_arr(t_list **env_llst, t_list **env_llst_sorted, char **arr);


void	test_parser_export(t_list **env_llst, t_list **env_llst_sorted,
			char *str);
void	export_single_arg(t_list **env_llst,
			t_list **env_llst_sorted, char *str);
void	update_or_create_llst_var(t_list **env_llst,
			t_list **env_llst_sorted, t_var_names *var);

			
void	update_util_env(t_list **env_llst, t_var_names *var, char *env_var_with_value);
void	update_util_export(t_list **env_llst_sorted, t_var_names *var, char *exp_var_with_value);

void	show_var_names(t_var_names *var);

// export b
void	get_var_names(t_var_names *var, char *str);
int		check_var_name(char *str);
int		check_first_c(char c);
int		check_other_c(char c);

// unset
void	test_parser_unset(t_list **env_llst, t_list **env_llst_sorted,
			char *str);
t_list	*find_var_in_llst(t_list **llst, char *var);

// Utils
// history
void	history_master(t_list **history_lst);
void	load_history_llst(char *hist_file_name, t_list **history_lst);
void	write_history_llst(char *hist_file_name, t_list **history_lst);
void	show_history_llist(t_list **lst);
void	add_history_llst_to_prompt(t_list **history_lst);
void	limit_history_llst(t_list **history_lst);

//util_lst

void	lst_delete_first(t_list **llist);
void	lst_dealloc(t_list **llist, int free_content);

void	copy_llst(t_list **src_llst, t_list **new_llst);
void	swap_nodes(t_list *a, t_list *b);
void	sort_list(t_list *head);
void	delete_node_from_llst(t_list **head, t_list *node_to_delete);

void	update_content_in_node(t_list *node, char *new_content);

// util lst c
void	get_val_of_var_value_allocation(char *v_name, void *cont,
			char **tmp_value);
char	*get_val_of_var(t_list **llst, char *var_name);

// util_string

char	*get_string_till_first_symbol(char *str_in, char symbol);
char	*get_string_without_symbols(char *str_in, char symbol);
char	*get_string_with_symbols_at_end_and_front(char *str_in, char symbol);
char	*get_string_from_first_symbol(char *str_in, char symbol);
char	*get_string_from_string(char *str_in);

char	*join_three_string(char *str1, char *str2, char *str3);

int		get_first_symbol_pos(char *str, char symbol);
int		find_newline(char *str);
void	del_first_nl(char *str);
int		has_str_symbol(char *str, char symbol);
int		is_s_in_pos_of_str(char *str, int pos, char symbol);

// Colors
void	c_red(void);
void	c_green(void);
void	c_blue(void);
void	c_purple(void);
void	c_yellow(void);
void	c_cyan(void);
void	clear_screen(void);
void	c_reset(void);
void	intro(void);
void	intro2(void);
void	intro3(void);

// utils dealloc
void	ini_var_names_to_null(t_var_names *var); // XXX muss woanders hin
void	dealloc_var_names(t_var_names *var);
void	free_n_null(void **ptr);

// Jonas Temp
void	show_var_names(t_var_names *var);

// Test Temp
void	test_var_names(t_list	*env_llst, t_list	*env_llst_sorted);
void	test_export_arg_array(t_list	*env_llst, t_list	*env_llst_sorted);
void	test_get_val_of_var(t_list	*env_llst, t_list	*env_llst_sorted);
void	test_echo(void);

// pwd
void	builtin_pwd(t_list **env_llst, t_list **env_llst_sorted, int print_pwd);

// CD
//void	builtin_cd(t_list **env_llst, t_list **env_llst_sorted,char *in);
void	builtin_cd_change_dir(t_list **env_llst, t_list **env_llst_sorted, char *path);
	
void test_change_dir(void);
void test_getcwd(void);
void test_opendir(void);
void test_is_dir_valid(char *dir);


#endif