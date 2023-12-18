/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:51:47 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/14 15:01:50 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**add_slash(char	**paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while(paths[i] != 0)
	{
		tmp = ft_strjoin(paths[i], "/");
		if (tmp == 0)
		{
			ft_strsfree(paths);
			return (0);
		}
		free(paths[i]);
		paths[i] = tmp;
		i++;
	}
	return (paths);
}

char	**get_paths(char	*envp[])
{
	char	*path_str;
	char	**paths;

	while(*envp != 0)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
		{
			path_str = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
			if (path_str == 0)
				return (0);
			paths = ft_split(path_str, ':');
			free(path_str);
			if (paths == 0)
				return (0);
			return(add_slash(paths));
		}
		envp++;
	}
	return (0);
}

int	main(int argc, char **argv, char *envp[])
{
	char	***commands;
	char	**paths;
	int		file_fds[2];
	int		exit_code;

	if (argc < 5)
	{
		errno = EINVAL;
		perror("not enough arguments");
		return (1);
	}
	exit_code = 0;
	paths = get_paths(envp);
	commands = setup_commands(argc - 3, argv + 2, &exit_code, paths);
	ft_strsfree(paths);
	if (commands == 0)
		return (0);
	if (set_files(argc, argv, file_fds) == -1)
	{
		free_commands(commands);
		return (1);
	}
	pipe_commands(file_fds, commands);
	free_commands(commands);
	return (exit_code);
}
