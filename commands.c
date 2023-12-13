/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:37:03 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/13 14:48:06 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strsfree(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != 0)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (0);
}

int	run_command_path(char **argv, char *path)
{
	char	*command;

	command = ft_strjoin(path, argv[0]);
	if (command == NULL)
		return (0);
	if (execve(command, argv, NULL) == -1)
	{
		free(command);
		return (-1);
	}
	free(command);
	return (1);
}

int	run_command(int input_fd, int output_fd, char *command)
{
	char	**argv;

	if (dup2(input_fd, 0) == -1 || dup2(output_fd, 1) == -1)
	{
		perror("dup failed");
		return (-1);
	}
	argv = ft_split(command, ' ');
	if (argv == NULL)
		return (0);
	if (run_command_path(argv, "/bin/") == -1)
		run_command_path(argv, "/usr/bin/");
	ft_strsfree(argv);
	return (1);
}
