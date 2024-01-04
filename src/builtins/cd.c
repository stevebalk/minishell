/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:05:04 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/04 13:54:18 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"
/*
The cd command in Bash (Bourne Again SHell) is used for changing the current working directory. Here are various ways you can use the cd command with different types of path specifications:

Absolute Path: Specify the full path from the root directory.
Example: cd /usr/local/bin

Relative Path: Specify the path relative to the current directory.
Example: cd Documents/Projects (Moves into the 'Projects' directory inside 'Documents' from the current directory)

Home Directory (~): This represents the user's home directory.
Example: cd ~ or simply cd (Moves to the user's home directory)

Parent Directory (..): Moves up one directory level.
Example: cd .. (Moves to the parent directory of the current directory)

Current Directory (.): Represents the current directory.
Example: cd . (Stays in the current directory)

Dash (-): Moves to the last working directory.
Example: cd - (Switches between the current and last directories)
OLDPWD  in environment

Environment Variables: Use environment variables in the path.
Example: cd $HOME/Downloads (Moves to the 'Downloads' directory inside the user's home directory)

Subshell Expansion: Navigate to directories using command substitution.
Example: cd $(dirname $(which python)) (Moves to the directory where the Python executable is located)

Brace Expansion: Useful for navigating to similarly named directories.
Example: cd /usr/{local,bin} (This will try to move to '/usr/local', and if it fails, it will try '/usr/bin')

These are the common ways to use the cd command in Bash. The actual path you specify will depend on the directory structure of your system and where you want to navigate.
*/

/*
Jonas:
.. and . works fine ... nothing to do

~(home directory)		does not work 

Fehlermeldung wenn Verzeichnis nicht vorhanden
cd pipp
bash: cd: pipp: No such file or directory

Fehlermeldung wenn Rechte nicht passen
mkdir TEST
bash-3.2$ chmod 000 TEST
bash-3.2$ cd TEST/
bash: cd: TEST/: Permission denied

export HOME=/Users/jonas/shelltests/nonexistingfolder			---> works, but 
cd ~				---> does NOT work
bash: cd: /Users/jonas/shelltests/nonexistingfolder: No such file or directory


After starting a new Terminal
cd -
bash: cd: OLDPWD not set
*/

static void	builtin_cd_if_a(t_ms *ms, int *exit_code)
{
	char	*tmp_str;

	tmp_str = get_val_of_var(&ms->env_llst, "HOME");
	if (tmp_str)
		*exit_code = builtin_cd_change_dir(&ms->env_llst,
				&ms->env_llst_sorted, tmp_str);
	else
	{
		perror("cd: HOME not set\n");
		*exit_code = 1;
	}
	free_n_null((void **)&tmp_str);
}

static void	builtin_cd_if_b(t_ms *ms, int *exit_code)
{
	char	*tmp_str;

	tmp_str = get_val_of_var(&ms->env_llst, "OLDPWD");
	if (!tmp_str)
	{
		c_red();
		printf("minishell: cd: OLDPWD not set\n");
		c_reset();
		*exit_code = 1;
	}
	else
	{
		*exit_code = builtin_cd_change_dir(&ms->env_llst,
				&ms->env_llst_sorted, tmp_str);
		builtin_pwd(&ms->env_llst, &ms->env_llst_sorted, 1);
		free_n_null((void **)&tmp_str);
	}
}

int	builtin_cd(t_ms *ms, t_list **env_llst, t_list **env_llst_sorted, char *in)
{
	int		exit_code;
	
	(void)env_llst;
	(void)env_llst_sorted;
	exit_code = 0;	
	if ((!in) || (ft_strncmp(in, "", 0) == 0 && ft_strlen(in) == 0))
		builtin_cd_if_a(ms, &exit_code);
	else if (ft_strncmp(in, "-", 1) == 0 && ft_strlen(in) == 1)
		builtin_cd_if_b(ms, &exit_code);
	else if (ft_strncmp(in, "~", 1) == 0 && ft_strlen(in) == 1)
		exit_code = builtin_cd_change_dir(&ms->env_llst,
				&ms->env_llst_sorted, ms->home_dir);
	else
		exit_code = builtin_cd_change_dir(&ms->env_llst,
				&ms->env_llst_sorted, in);
	return (exit_code);
}

static int	builtin_cd_chge_dir_pwd(t_list **env_llst, t_list **env_llst_sorted, char *path, int exit_code)
{
	char	*tmp_value;
	char	*last_pwd;

	last_pwd = get_val_of_var(env_llst, "PWD");
	if (exit_code != 0)
	{
		c_red();
		fflush(stdout);
		ft_putstr_fd("minishell", 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		c_reset();
		free_n_null((void **)&last_pwd);
		exit_code = 1;
	}
	else
	{
		tmp_value = join_three_string("OLDPWD", "=", last_pwd);
		export_single_arg(env_llst, env_llst_sorted, tmp_value);
		builtin_pwd(env_llst, env_llst_sorted, 0);
		free(tmp_value);
	}
	free_n_null((void **)&last_pwd);
	return (exit_code);
}

int	builtin_cd_change_dir(t_list **env_llst, t_list **env_llst_sorted, char *path)
{
	int		exit_code;
	//char	*last_pwd;
	//char	*tmp_value;

	exit_code = 0;
	if (!path)
		return (exit_code = 1, exit_code);

	exit_code = chdir(path);

	exit_code = builtin_cd_chge_dir_pwd(env_llst, env_llst_sorted, path, exit_code);
	
	// if (exit_code != 0)
	// {
	// 	c_red();
	// 	fflush(stdout);
	// 	ft_putstr_fd("minishell", 2);
	// 	ft_putstr_fd(": ", 2);
	// 	ft_putstr_fd(path, 2);
	// 	ft_putstr_fd(": ", 2);
	// 	perror("");
	// 	c_reset();
	// 	free_n_null((void **)&last_pwd);
	// return (exit_code = 1, exit_code);
	// }
	// else
	// {
	// 	tmp_value = join_three_string("OLDPWD", "=", last_pwd);
	// 	export_single_arg(env_llst, env_llst_sorted, tmp_value);
	// 	builtin_pwd(env_llst, env_llst_sorted, 0);
	// 	free(tmp_value);
	// }
	//free_n_null((void **)&last_pwd);
	return (exit_code);
}



// ######## TEST ########
// #############   OLD Test Stuff   ###############
// void test_change_dir(void) 
// {
//     //const char *path = "../"; // 
// 	//const char *path = ".."; 			// works
// 	//const char *path = "."; 			// works

	
// 	//const char *path = "~"; 			// not work			--> go to home dir
// 	//const char *path = "-"; 			// not work			--> go to last working! dir

// 	const char *path = "./libs/libft"; 

// 	c_yellow(); printf("test_change_dir()\n"); c_reset();
	
//     // Change the current working directory
//     if (chdir(path) != 0) 
// 	{
//         c_red(); perror("chdir failed");c_reset();
//         exit(EXIT_FAILURE);
//     }

// 	builtin_pwd(NULL, NULL, 1);
	

// 	c_red(); printf("~test_change_dir()\n"); c_reset();
// }

// void test_getcwd(void)
// {
// 	c_yellow(); printf("test_get_cwd()\n"); c_reset();

// 	char *buffer;
//     size_t size = 1024;

//     // Allocate memory for the buffer
//     buffer = (char *)malloc(size * sizeof(char));
//     if (buffer == NULL) 
// 	{
//         perror("Unable to allocate buffer");
//         exit(1);
//     }

//     // Get the current working directory
// 	if (getcwd(buffer, size) == NULL) 
// 	{
//         perror("Error getting current directory");
//         exit(1);
// 	}

//     // Print the current working directory
//     printf("Current working directory: %s\n", buffer);

//     // Free the allocated memory
//     free(buffer);

//     //return 0;
// }


// void test_opendir(void)
// {
// 	DIR *d;
//     struct dirent *dir;
// 	c_yellow(); printf("test_opendir()\n"); c_reset();

//     d = opendir("."); // Open the current directory
//     if (d) 
// 	{
//         while ((dir = readdir(d)) != NULL) 
// 		{
//             printf("%s\n", dir->d_name); // Print the name of the entry
//         }
//         closedir(d); // Close the directory
//     }
// 	else 
// 	{
//         perror("Unable to open directory");
//         exit(EXIT_FAILURE);
//     }

// }

// void test_is_dir_valid(char *dir)
// {
// 	c_yellow(); printf("test_is_dir_valid()  dir >%s<\n", dir); c_reset();

// 	DIR *d;
// 	d = opendir(dir);	
	
// 	if (d)
// 	{
// 		c_green();printf("dir >%s< exists()\n", dir); c_reset();
// 	}	
// 	else
// 	{
// 		c_red();printf("dir >%s< NOT exists()\n", dir); c_reset();
// 	}
// 	closedir(d);
		
// }