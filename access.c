/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:44:18 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/12 17:16:27 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	r_access_open(t_pipex *pipex)
{
	int	fd;

	if (access(pipex->input, F_OK) == -1)
	{
		existence_error(pipex->input);
		exit(0);
	}
	if (access(pipex->input, R_OK) == -1)
	{
		permission_error(pipex->input);
		exit(0);
	}
	fd = open(pipex->input, O_RDONLY);
	if (fd == -1)
		error_exit("open", pipex);
	return (fd);
}

int	w_access_open(t_pipex *pipex)
{
	int	fd;

	if (access(pipex->output, F_OK) != -1 && access(pipex->output, W_OK) == -1)
	{
		permission_error(pipex->output);
		exit(0);
	}
	if (ft_strncmp(pipex->input, "here_doc", 9) == 0)
		fd = open(pipex->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(pipex->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_exit("open", pipex);
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
		error_exit("malloc", pipex);
	ft_strlcpy(concat, path, path_len + 1);
	concat[path_len] = '/';
	ft_strlcat(concat, file, path_len + file_len + 2);
	return (concat);
}

// int	command_execve(t_pipex *pipex, int n, int in_fd, int out_fd)
// {
// 	int		i;
// 	char	*path;

// 	i = 0;
// 	while (pipex->env_path[i])
// 	{
// 		path = concat_path(pipex->env_path[i], pipex->command[n][0], pipex);
// 		if (access(path, F_OK) != -1)
// 		{
// 			if (access(path, X_OK) == -1)
// 				permission_error(path);
// 			else if (fork_execve(path, 
// pipex->command[n][0], in_fd, out_fd) == -1)
// 				exit(0);
// 			free(path);
// 			return ;
// 		}
// 		free(path);
// 		++i;
// 	}
// 	command_error(pipex->command[n][0]);
// }

// void	access_execve(t_pipex *pipex, int n, int in_fd, int out_fd)
// {
// 	if (pipex->command[n][0][0] == '\0')
// 		command_error("");
// 	else if (ft_strchr(pipex->command[n][0], '/') == NULL)
// 		command_execve(pipex, n, in_fd, out_fd);
// 	else if (access(pipex->command[n][0], F_OK) == -1)
// 		existence_error(pipex->command[n][0]);
// 	else if (access(pipex->command[n][0], X_OK) == -1)
// 		permission_error(pipex->command[n][0]);
// 	else
// 	{
// 		if (fork_execve(pipex-
// >command[n][0], pipex->command[n], in_fd, out_fd) == -1)
// 			exit(0);
// 	}
// }

char	*add_env(t_pipex *pipex, int n)
{
	int		i;
	char	*path;

	if (pipex->env_path[0] == NULL)
	{
		existence_error(pipex->command[n][0]);
		exit(0);
	}
	i = 0;
	while (pipex->env_path[i])
	{
		path = concat_path(pipex->env_path[i], pipex->command[n][0], pipex);
		if (access(path, F_OK) != -1)
		{
			if (access(path, X_OK) != -1)
				return (path);
			permission_error(path);
			exit(0);
		}
		free(path);
		++i;
	}
	command_error(pipex->command[n][0]);
	exit(0);
}

char	*command_path(t_pipex *pipex, int n)
{
	if (pipex->command[n][0][0] == '\0')
	{
		command_error("");
		exit(0);
	}
	if (ft_strchr(pipex->command[n][0], '/') == NULL)
		return (add_env(pipex, n));
	if (access(pipex->command[n][0], F_OK) == -1)
	{
		existence_error(pipex->command[n][0]);
		exit(0);
	}
	if (access(pipex->command[n][0], X_OK) == -1)
	{
		permission_error(pipex->command[n][0]);
		exit(0);
	}
	return (pipex->command[n][0]);
}
