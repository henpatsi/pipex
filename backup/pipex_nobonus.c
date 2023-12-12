/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_nobonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:51:47 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/12 14:05:59 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	set_files(int argc, char **argv, int *file_fds)
{
	int	infile_fd;
	int	outfile_fd;

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
	{
		perror(argv[1]);
		return (-1);
	}
	outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT, 0666);
	if (outfile_fd == -1)
	{
		close(infile_fd);
		perror(argv[argc - 1]);
		return (-1);
	}
	file_fds[0] = infile_fd;
	file_fds[1] = outfile_fd;
	return (1);
}

int	main(int argc, char **argv)
{
	int		file_fds[2];
	int		pipe_fds[2];
	pid_t	process_id;
	int		command_i;

	if (argc < 5)
	{
		ft_putstr_fd("not enough arguments\n", 2);
		return (-1);
	}

	if (set_files(argc, argv, file_fds) == -1)
		return (0);
		
	if (pipe(pipe_fds) < 0)
	{
		perror("pipe failed");
		return (0);
	}

	command_i = 2;
	while (command_i < argc - 1)
	{
		process_id = fork();

		if (process_id < 0)
		{
			perror("fork failed");
			return (0);
		}
		else if (process_id > 0)
		{
			close(pipe_fds[1]);
			wait(0);
		}
		else if (process_id == 0)
		{
			if (command_i == 2)
			{
				close(pipe_fds[0]);
				if (dup2(file_fds[0], 0) == -1)
					perror("dup failed");
				if (dup2(pipe_fds[1], 1) == -1)
					perror("dup failed");
			}
			else if (command_i == argc - 2)
			{
				close(pipe_fds[1]);
				if (dup2(pipe_fds[0], 0) == -1)
					perror("dup failed");
				if (dup2(file_fds[1], 1) == -1)
					perror("dup failed");
			}
			if (run_command(argv[command_i]) == -1)
				break;
		}
		command_i++;
	}
	return (0);
}
