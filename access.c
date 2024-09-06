/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:44:18 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/06 15:07:45 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	r_access_open(char *file)
{
	int	fd;

	if (access(file, F_OK) == -1)
	{
		existence_error(file);
		return (-1);
	}
	if (access(file, R_OK) == -1)
	{
		permission_error(file);
		return (-1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_putstr_fd("open error\n", 2);
	return (fd);
}

int	w_access_open(char *file, char *input)
{
	int	fd;

	if (access(file, F_OK) != -1 && access(file, W_OK) == -1)
	{
		permission_error(file);
		return (-1);
	}
	if (ft_strncmp(input, "here_doc", 9) == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_putstr_fd("open error\n", 2);
	return (fd);
}

char	*concat_path(char *path, char *file, t_pipex *pipex)
{
	char	*concat;
	size_t	path_len;
	size_t	file_len;

	(void)pipex;
	path_len = ft_strlen(path);
	file_len = ft_strlen(file);
	concat = ft_calloc(path_len + file_len + 2, 1);
	if (concat == NULL)
	{
		ft_putstr_fd("malloc error\n", 2);
		exit(0);
	}
	ft_strlcpy(concat, path, path_len + 1);
	concat[path_len] = '/';
	ft_strlcat(concat, file, path_len + file_len + 2);
	return (concat);
}

void	command_execve(t_pipex *pipex, int n)
{
	int		i;
	char	*path;

	i = 0;
	while (pipex->env_path[i])
	{
		path = concat_path(pipex->env_path[i], pipex->command[n][0], pipex);
		if (access(path, F_OK) != -1)
		{
			if (access(path, X_OK) == -1)
				permission_error(path);
			else
				fork_execve(pipex, path, n);
			free(path);
			return ;
		}
		free(path);
		++i;
	}
	command_error(pipex->command[n][0]);
}

void	access_execve(t_pipex *pipex, int n)
{
	if (ft_strchr(pipex->command[n][0], '/') == NULL)
		command_execve(pipex, n);
	else if (access(pipex->command[n][0], F_OK) == -1)
		existence_error(pipex->command[n][0]);
	else if (access(pipex->command[n][0], X_OK) == -1)
		permission_error(pipex->command[n][0]);
	else
		fork_execve(pipex, pipex->command[n][0], n);
}
