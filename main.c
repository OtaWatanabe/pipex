/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:21:58 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/12 17:34:03 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q pipex");
// }

char	**get_env_path(char *env[])
{
	int		i;
	char	**ret;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_split(env[i] + 5, ':'));
		++i;
	}
	ret = ft_calloc(sizeof(char *), 1);
	return (ret);
}

void	set_heredoc(t_pipex *pipex, char *limiter)
{
	--pipex->command_num;
	pipex->limiter = limiter;
	if (pipex->command_num == 1)
		error_exit("arguments", pipex);
}

void	set_commands(t_pipex *pipex, char *argv[])
{
	int	i;

	if (ft_strncmp(pipex->input, "here_doc", 9) == 0)
	{
		set_heredoc(pipex, argv[2]);
		++argv;
	}
	pipex->command = malloc(sizeof(char **) * pipex->command_num);
	if (pipex->command == NULL)
		error_exit("malloc", pipex);
	i = 1;
	while (i++ <= pipex->command_num)
	{
		if (argv[i][0] == ' ' || argv[i][0] == '\0')
		{
			pipex->command[i - 2] = ft_calloc(sizeof(char *) * 2, 1);
			if (pipex->command[i - 2] == NULL)
				error_exit("malloc", pipex);
			pipex->command[i - 2][0] = argv[i];
			continue ;
		}
		pipex->command[i - 2] = ft_split(argv[i], ' ');
		if (pipex->command[i - 2] == NULL)
			error_exit("malloc", pipex);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	if (argc < 5)
		error_exit("arguments", &pipex);
	pipex.input = argv[1];
	pipex.output = argv[argc - 1];
	pipex.env = env;
	pipex.command_num = argc - 3;
	pipex.env_path = get_env_path(env);
	if (pipex.env_path == NULL)
		error_exit("malloc", &pipex);
	set_commands(&pipex, argv);
	execute(&pipex);
}
