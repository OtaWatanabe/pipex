/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:48:04 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/12 16:39:53 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	initial_execve(t_pipex *pipex)
{
	int		pipe_fd[2];
	pid_t	p;

	if (ft_strncmp(pipex->input, "here_doc", 9) == 0)
		return (here_doc(pipex));
	if (pipe(pipe_fd) == -1)
		error_exit("pipe", pipex);
	p = fork();
	if (p == -1)
		error_exit("fork", pipex);
	if (p != 0)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	open_execve(pipex, pipe_fd);
	return (-1);
}

int	middle_execve(int in_fd, t_pipex *pipex, int n)
{
	int		pipe_fd[2];
	pid_t	p;

	if (pipe(pipe_fd) == -1)
		error_exit("pipe", pipex);
	p = fork();
	if (p == -1)
		error_exit("fork", pipex);
	if (p != 0)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	pipe_execve(pipex, pipe_fd, in_fd, n);
	return (-1);
}

void	last_execve(int in_fd, t_pipex *pipex, int n)
{
	int		out_fd;
	pid_t	p;
	char	*path;

	p = fork();
	if (p == -1)
		error_exit("pipe", pipex);
	if (p != 0)
	{
		close(in_fd);
		return ;
	}
	out_fd = w_access_open(pipex);
	path = command_path(pipex, n);
	if (dup2(in_fd, 0) == -1 || dup2(out_fd, 1) == -1)
		error_exit("dup2", pipex);
	close(in_fd);
	close(out_fd);
	if (execve(path, pipex->command[n], pipex->env) == -1)
		exit(0);
}

void	execute(t_pipex *pipex)
{
	int		fd;
	int		i;

	fd = initial_execve(pipex);
	i = 1;
	while (i < pipex->command_num - 1)
	{
		fd = middle_execve(fd, pipex, i);
		++i;
	}
	last_execve(fd, pipex, i);
	i = 0;
	while (i++ < pipex->command_num)
		wait(NULL);
	if (ft_strncmp(pipex->input, "here_doc", 9) == 0)
		unlink(pipex->tmp);
	exit(0);
}
