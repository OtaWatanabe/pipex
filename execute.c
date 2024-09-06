/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:48:04 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/06 15:07:56 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	*initial_execve(t_pipex *pipex)
{
	int	fd;
	int	*pipe_fd;

	if (ft_strncmp(pipex->input, "here_doc", 9) == 0)
		return (here_doc(pipex));
	fd = r_access_open(pipex->input);
	pipe_fd = set_pipe(pipex);
	if (fd == -1)
	{
		close(pipe_fd[1]);
		return (pipe_fd);
	}
	if (dup2(fd, 0) == -1)
	{
		ft_putstr_fd("dup2 error\n", 2);
		exit(0);
	}
	access_execve(pipex, 0);
	close(pipe_fd[1]);
	close(fd);
	return (pipe_fd);
}

int	*middle_execve(int *fd, t_pipex *pipex, int n)
{
	int	*pipe_fd;

	if (dup2(fd[0], 0) == -1)
	{
		ft_putstr_fd("dup2 error\n", 2);
		exit(0);
	}
	pipe_fd = set_pipe(pipex);
	access_execve(pipex, n);
	close(pipe_fd[1]);
	close(fd[0]);
	free(fd);
	return (pipe_fd);
}

void	last_execve(int *fd, t_pipex *pipex)
{
	int	fd_out;

	fd_out = w_access_open(pipex->output, pipex->input);
	if (fd_out == -1)
		exit(0);
	if (dup2(fd[0], 0) == -1 || dup2(fd_out, 1) == -1)
	{
		ft_putstr_fd("dup2 error\n", 2);
		exit(0);
	}
	access_execve(pipex, pipex->command_num - 1);
	close(fd[0]);
	free(fd);
	close(fd_out);
}

void	execute(t_pipex *pipex)
{
	int		*fd;
	int		i;

	fd = initial_execve(pipex);
	i = 1;
	while (i < pipex->command_num - 1)
	{
		fd = middle_execve(fd, pipex, i);
		++i;
	}
	last_execve(fd, pipex);
	exit(0);
}
