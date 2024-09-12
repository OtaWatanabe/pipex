/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:08:54 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/12 16:35:33 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "get_next_line.h"

typedef struct s_pipex
{
	int		command_num;
	char	*input;
	char	*output;
	char	***command;
	char	**env;
	char	**env_path;
	char	*limiter;
	char	*tmp;
}	t_pipex;

void	execute(t_pipex *pipex);
int		initial_execve(t_pipex *pipex);
int		*set_pipe(t_pipex *pipex);
void	access_execve(t_pipex *pipex, int n, int *fd);
int		r_access_open(t_pipex *pipex);
void	existence_error(char *path);
void	permission_error(char *path);
void	fork_execve(t_pipex *pipex, char *path, int n, int *fd);
int		w_access_open(t_pipex *pipex);
void	command_error(char *command);
int		here_doc(t_pipex *pipex);
void	error_exit(char *msg, t_pipex *pipex);
char	*command_path(t_pipex *pipex, int n);
char	*add_env(t_pipex *pipex, int n);
void	open_execve(t_pipex *pipex, int *pipe_fd);
void	pipe_execve(t_pipex *pipex, int *pipe_fd, int in_fd, int n);

#endif