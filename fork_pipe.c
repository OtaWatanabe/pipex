/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:13:15 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/12 16:58:17 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

// int	*set_pipe(t_pipex *pipex)
// {
// 	int	*fd;

// 	(void)pipex;
// 	fd = malloc(sizeof(int) * 2);
// 	if (fd == NULL)
// 		error_exit("malloc", pipex);
// 	if (pipe(fd) == -1)
// 		error_exit("pipe", pipex);
// 	if (dup2(fd[1], 1) == -1)
// 		error_exit("dup2", pipex);
// 	close(fd[1]);
// 	return (fd);
// }

// int	fork_execve(char *path, char **command, int in_fd, int out_fd)
// {
// 	pid_t	p;

// 	if (dup2(in_fd, 0) == -1 || dup2(out_fd, 1) == -1)
// 	{
// 		ft_putstr_fd("dup2 error\n", 2);
// 		return (-1);
// 	}
// 	p = fork();
// 	if (p == -1)
// 	{
// 		ft_putstr_fd("fork error\n", 2);
// 		return (-1);
// 	}
// 	if (p == 0)
// 	{
// 		if (execve(path, pipex->command[n], pipex->env) == -1)
// 			error_exit("execve", pipex);
// 	}
// 	ft_putnbr_fd(p, 2);
// 	ft_putchar_fd('\n', 2);
// }

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
