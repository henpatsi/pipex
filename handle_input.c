/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:57:27 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/14 14:51:05 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static const char	*g_paths[7] = {"/usr/local/bin/", "/usr/bin/", "/bin/",
	"/usr/sbin/", "/sbin/", 0};

char	*add_path(char *command, int *ec_ptr)
{
	char	*path_command;
	int		i;

	i = 0;
	while (g_paths[i] != 0)
	{
		path_command = ft_strjoin(g_paths[i], command);
		if (path_command == 0)
			return (0);
		if (access(path_command, X_OK) != -1)
			return (path_command);
		free(path_command);
		i++;
	}
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	*ec_ptr = 127;
	return (ft_strdup(command));
}

char	**create_command(char *command_str, int *ec_ptr)
{
	char	**command_arr;
	char	*path_command;

	command_arr = ft_split(command_str, ' ');
	if (command_arr == 0)
		return (0);
	path_command = add_path(command_arr[0], ec_ptr);
	if (path_command == 0)
	{
		ft_strsfree(command_arr);
		return (0);
	}
	free(command_arr[0]);
	command_arr[0] = path_command;
	return (command_arr);
}

char	***setup_commands(int command_count, char **argv_commands, int *ec_ptr)
{
	char	***commands;
	int		i;

	commands = malloc((command_count + 1) * sizeof(char **));
	if (commands == 0)
		return (0);
	i = 0;
	while (i < command_count)
	{
		commands[i] = create_command(argv_commands[i], ec_ptr);
		if (commands[i] == 0)
		{
			free_commands(commands);
			return (0);
		}
		i++;
	}
	commands[i] = 0;
	return (commands);
}

int	set_files(int argc, char **argv, int *file_fds)
{
	file_fds[0] = open(argv[1], O_RDONLY);
	if (file_fds[0] == -1)
		perror(argv[1]);
	file_fds[1] = open(argv[argc - 1], O_RDWR | O_CREAT, 0666);
	if (file_fds[1] == -1)
	{
		close(file_fds[0]);
		perror(argv[argc - 1]);
		return (-1);
	}
	return (1);
}
