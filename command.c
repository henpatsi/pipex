/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:37:03 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/12 14:03:52 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

int	run_command(char *command)
{
	char	**argv;

	argv = ft_split(command, ' ');
	if (argv == NULL)
		return (0);
	if (argv == NULL)
		return (0);
	if (run_command_path(argv, "/bin/") == -1
		&& run_command_path(argv, "/usr/bin/") == -1)
	{
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": command not found", 2);
		return (-1);
	}
	ft_strsfree(argv);
	return (1);
}