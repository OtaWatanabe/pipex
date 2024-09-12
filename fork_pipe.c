/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:13:15 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/12 17:33:41 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	pipe_execve(t_pipex *pipex, int *pipe_fd, int in_fd, int n)
{
	char	*path;

	path = command_path(pipex, n);
	if (dup2(in_fd, 0) == -1 || dup2(pipe_fd[1], 1) == -1)
		error_exit("dup2", pipex);
	close(in_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	if (execve(path, pipex->command[n], pipex->env) == -1)
		exit(0);
}

void	open_execve(t_pipex *pipex, int *pipe_fd)
{
	int		in_fd;
	char	*path;

	in_fd = r_access_open(pipex);
	path = command_path(pipex, 0);
	if (dup2(in_fd, 0) == -1 || dup2(pipe_fd[1], 1) == -1)
		error_exit("dup2", pipex);
	close(in_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	if (execve(path, pipex->command[0], pipex->env) == -1)
		exit(0);
}
