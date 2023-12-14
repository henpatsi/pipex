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

int	main(int argc, char **argv)
{
	char	***commands;
	int		file_fds[2];
	int		exit_code;

	if (argc < 5)
	{
		errno = EINVAL;
		perror("not enough arguments");
		return (1);
	}
	exit_code = 0;
	commands = setup_commands(argc - 3, argv + 2, &exit_code);
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
