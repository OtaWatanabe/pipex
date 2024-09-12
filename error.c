/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:52:14 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/12 11:29:32 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

// char	*free_strjoin(char *s1, char *s2)
// {
// 	char	*p;
// 	size_t	i;
// 	size_t	j;

// 	if (s1 == NULL || s2 == NULL)
// 		return (NULL);
// 	p = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
// 	if (p)
// 	{
// 		i = 0;
// 		while (s1[i])
// 		{
// 			p[i] = s1[i];
// 			i++;
// 		}
// 		j = 0;
// 		while (s2[j])
// 		{
// 			p[i + j] = s2[j];
// 			j++;
// 		}
// 	}
// 	free(s1);
// 	return (p);
// }

void	existence_error(char *path)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	permission_error(char *path)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

void	command_error(char *command)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	error_exit(char *msg, t_pipex *pipex)
{
	(void)pipex;
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" error\n", 2);
	exit(0);
}
