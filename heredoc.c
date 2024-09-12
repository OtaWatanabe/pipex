/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:20:12 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/12 17:24:26 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	*get_random(int n)
{
	char	*ret;
	int		i;

	ret = ft_calloc(n + 14, 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < 12)
	{
		ret[i] = "/tmp/tmpfile"[i];
		++i;
	}
	while (i - 12 < n)
	{
		ret[i] = '+';
		++i;
	}
	return (ret);
}

char	*get_filename(void)
{
	char	*random;
	int		i;

	random = get_random(0);
	if (random == NULL)
	{
		ft_putstr_fd("malloc error\n", 2);
		return (NULL);
	}
	i = 1;
	while (access(random, F_OK) != -1)
	{
		free(random);
		random = get_random(i);
		if (random == NULL)
		{
			ft_putstr_fd("malloc error\n", 2);
			return (NULL);
		}
		++i;
	}
	return (random);
}

void	read_doc(int fd, t_pipex *pipex)
{
	char	*line;

	line = get_next_line(0);
	if (line == NULL)
		error_exit("read", pipex);
	while (ft_strncmp(line, pipex->limiter, ft_strlen(pipex->limiter)) != 0
		|| line[ft_strlen(pipex->limiter)] != '\n')
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
		if (line == NULL)
		{
			close(fd);
			error_exit("read", pipex);
		}
	}
	free(line);
}

// int	*pipe_doc(int fd, t_pipex *pipex, char *tmp)
// {
// 	int	*pipe_fd;

// 	pipe_fd = set_pipe(pipex);
// 	if (dup2(fd, 0) == -1)
// 		error_exit("dup2", pipex);
// 	access_execve(pipex, 0);
// 	close(pipe_fd[1]);
// 	close(fd);
// 	unlink(tmp);
// 	free(tmp);
// 	return (pipe_fd);
// }

int	here_doc(t_pipex *pipex)
{
	int		fd;
	int		pipe_fd[2];
	pid_t	p;

	pipex->tmp = get_filename();
	if (pipex->tmp == NULL)
		exit(0);
	fd = open(pipex->tmp, O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
		error_exit("open", pipex);
	read_doc(fd, pipex);
	close(fd);
	if (pipe(pipe_fd) == -1)
		error_exit("pipe", pipex);
	p = fork();
	if (p == 0)
	{
		fd = open(pipex->tmp, O_RDONLY);
		if (fd == -1)
			error_exit("open", pipex);
		pipe_execve(pipex, pipe_fd, fd, 0);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
