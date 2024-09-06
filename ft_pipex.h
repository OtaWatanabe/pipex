/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:08:54 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/06 15:13:52 by otawatanabe      ###   ########.fr       */
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
}	t_pipex;

void	execute(t_pipex *pipex);
int		*initial_execve(t_pipex *pipex);
int		*set_pipe(t_pipex *pipex);
void	access_execve(t_pipex *pipex, int n);
int		r_access_open(char *file);
void	existence_error(char *path);
void	permission_error(char *path);
void	fork_execve(t_pipex *pipex, char *path, int n);
int		w_access_open(char *file, char *input);
void	command_error(char *command);
int		*here_doc(t_pipex *pipex);

#endif