/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:51:47 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/12 16:16:47 by hpatsi           ###   ########.fr       */
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

int	file_to_pipe(int *file_fds, int *pipe_fds, char *command)
{
	int	process_id;

	process_id = fork();
	if (process_id < 0)
	{
		perror("fork failed");
	}
	else if (process_id > 0)
	{
		wait(0);
		close(file_fds[0]);
		close(pipe_fds[1]);
	}
	else
	{
		return (run_command(file_fds[0], pipe_fds[1], command));
	}
	return (0);
}

int	pipe_to_file(int *file_fds, int *pipe_fds, char *command)
{
	int	process_id;

	process_id = fork();
	if (process_id < 0)
	{
		perror("fork failed");
	}
	else if (process_id > 0)
	{
		wait(0);
		close(pipe_fds[0]);
		close(file_fds[1]);
	}
	else
	{
		close(pipe_fds[1]);
		return (run_command(pipe_fds[0], file_fds[1], command));
	}
	return (0);
}

int	pipe_to_pipe(int *pipe_fds, char *command)
{
	int	pipe2_fds[2];
	int	process_id;

	if (pipe(pipe2_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}

	process_id = fork();
	
	if (process_id < 0)
	{
		perror("fork failed");
	}
	else if (process_id > 0)
	{
		wait(0);
		close(pipe_fds[0]);
		close(pipe2_fds[1]);
		pipe_fds[0] = pipe2_fds[0];
		pipe_fds[1] = pipe2_fds[1];
	}
	else
	{
		return (run_command(pipe_fds[0], pipe2_fds[1], command));
	}
	return (0);
}

int	handle_many_commands(int argc, char **argv, int *pipe_fds)
{
	int command_i;

	command_i = 3;
	while (command_i < argc - 2)
	{
		//ft_printf("Starting command %s\n", argv[command_i]);
		pipe_to_pipe(pipe_fds, argv[command_i]);
		command_i++;
	}
	return (0);
}

void	handle_main(int argc, char **argv, int *file_fds)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) < 0)
	{
		perror("pipe failed");
		return ;
	}

	if (file_to_pipe(file_fds, pipe_fds, argv[2]) == -1)
		return ;
	if (argc > 5)
	{
		if (handle_many_commands(argc, argv, pipe_fds) == -1)
			return ;
	}
	pipe_to_file(file_fds, pipe_fds, argv[argc - 2]);
}

int	main(int argc, char **argv)
{
	int		file_fds[2];

	if (argc < 5)
	{
		ft_putstr_fd("not enough arguments\n", 2);
		return (0);
	}
	if (set_files(argc, argv, file_fds) == -1)
		return (0);
	handle_main(argc, argv, file_fds);
	return (0);
}
