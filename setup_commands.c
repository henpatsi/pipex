/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:57:27 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/21 10:42:17 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**add_slash(char	**paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i] != 0)
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

	while (*envp != 0)
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
			return (add_slash(paths));
		}
		envp++;
	}
	return (0);
}

char	*add_path(char *command, int *ec_ptr, char **paths)
{
	char	*path_command;
	int		i;

	i = 0;
	while (paths[i] != 0)
	{
		path_command = ft_strjoin(paths[i], command);
		if (path_command == 0)
			return (0);
		if (access(path_command, X_OK) != -1)
		{
			*ec_ptr = 0;
			return (path_command);
		}
		free(path_command);
		i++;
	}
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	*ec_ptr = 127;
	return (ft_strdup(command));
}

char	**create_command(char *command_str, int *ec_ptr, char **paths)
{
	char	**command_arr;
	char	*path_command;

	command_arr = ft_split(command_str, ' ');
	if (command_arr == 0)
		return (0);
	if (command_arr[0] == 0)
		return (command_arr);
	if (access(command_arr[0], X_OK) != -1)
		*ec_ptr = 0;
	else
	{
		path_command = add_path(command_arr[0], ec_ptr, paths);
		if (path_command == 0)
		{
			ft_strsfree(command_arr);
			return (0);
		}
		free(command_arr[0]);
		command_arr[0] = path_command;
	}
	return (command_arr);
}

char	***set_commands(int count, char **comm_strs, int *ec_ptr, char *envp[])
{
	char	***commands;
	int		i;
	char	**paths;

	commands = malloc((count + 1) * sizeof(char **));
	if (commands == 0)
		return (0);
	i = 0;
	paths = get_paths(envp);
	while (i < count)
	{
		commands[i] = create_command(comm_strs[i], ec_ptr, paths);
		if (commands[i] == 0)
		{
			free_commands(commands);
			ft_strsfree(paths);
			return (0);
		}
		i++;
	}
	ft_strsfree(paths);
	commands[i] = 0;
	return (commands);
}
