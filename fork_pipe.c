/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:13:15 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/06 15:12:05 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	*set_pipe(t_pipex *pipex)
{
	int	*fd;

	(void)pipex;
	fd = malloc(sizeof(int) * 2);
	if (fd == NULL)
	{
		ft_putstr_fd("malloc error\n", 2);
		exit(0);
	}
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("pipe error\n", 2);
		exit(0);
	}
	if (dup2(fd[1], 1) == -1)
	{
		ft_putstr_fd("dup2 error\n", 2);
		exit(0);
	}
	return (fd);
}

void	fork_execve(t_pipex *pipex, char *path, int n)
{
	pid_t	p;

	p = fork();
	if (p == -1)
	{
		ft_putstr_fd("fork error\n", 2);
		exit(0);
	}
	else if (p == 0)
	{
		if (execve(path, pipex->command[n], pipex->env) == -1)
		{
			ft_putstr_fd("execve error\n", 2);
			exit(0);
		}
	}
	else
	{
		wait(NULL);
		return ;
	}
}
