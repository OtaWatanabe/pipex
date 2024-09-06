/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:21:58 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/06 15:13:44 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q pipex");
// }

char	**get_env_path(char *env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			return (ft_split(env[i] + 5, ':'));
		}
		++i;
	}
	return (NULL);
}

void	set_heredoc(t_pipex *pipex, char *limiter)
{
	--pipex->command_num;
	pipex->limiter = limiter;
	if (pipex->command_num == 1)
	{
		ft_putstr_fd("arguments error\n", 2);
		exit(0);
	}
}

void	set_commands(t_pipex *pipex, char *argv[])
{
	int	i;
	int	j;

	j = 2;
	if (ft_strncmp(pipex->input, "here_doc", 9) == 0)
	{
		++j;
		set_heredoc(pipex, argv[2]);
	}
	pipex->command = malloc(sizeof(char **) * pipex->command_num);
	if (pipex->command == NULL)
	{
		ft_putstr_fd("malloc error\n", 2);
		exit(0);
	}
	i = 0;
	while (i < pipex->command_num)
	{
		pipex->command[i] = ft_split(argv[j++], ' ');
		if (pipex->command[i++] == NULL)
		{
			ft_putstr_fd("malloc error\n", 2);
			exit(0);
		}
	}
}

t_pipex	init(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	if (argc < 5)
	{
		ft_putendl_fd("arguments error\n", 2);
		exit(0);
	}
	pipex.input = argv[1];
	pipex.output = argv[argc - 1];
	pipex.env = env;
	pipex.command_num = argc - 3;
	pipex.env_path = get_env_path(env);
	if (pipex.env_path == NULL)
	{
		ft_putstr_fd("malloc error\n", 2);
		exit(0);
	}
	set_commands(&pipex, argv);
	return (pipex);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	pipex = init(argc, argv, env);
	execute(&pipex);
}
