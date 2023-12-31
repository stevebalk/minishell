/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:19:55 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/08 13:29:19 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_file_error(char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror("");
}

void	print_execution_error(char *path_name, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	command_not_found(t_cmd_io *io, char *cmd, char **env, char *path)
{
	if (io->in_fd != -1)
		close(io->in_fd);
	if (io->out_fd != -1)
		close(io->out_fd);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	ft_free_array((void **)env);
	if (path)
		free(path);
}

void	execve_error(t_cmd_io *io, char **env, char *path)
{
	if (io->in_fd != -1)
		close(io->in_fd);
	if (io->out_fd != -1)
		close(io->out_fd);
	ft_free_array((void **)env);
	if (path)
		free(path);
	print_file_error(path);
}
