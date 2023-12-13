/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:23:00 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/13 14:48:10 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	file_to_pipe(int *file_fds, int *pipe_fds, char *command)
{
	int	process_id;

	process_id = fork();
	if (process_id < 0)
		perror("fork failed");
	else if (process_id > 0)
	{
		wait(0);
		close(file_fds[0]);
		close(pipe_fds[1]);
	}
	else
	{
		close(pipe_fds[0]);
		return (run_command(file_fds[0], pipe_fds[1], command));
	}
	return (0);
}

int	pipe_to_file(int *file_fds, int *pipe_fds, char *command)
{
	int	process_id;

	process_id = fork();
	if (process_id < 0)
		perror("fork failed");
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
		perror("fork failed");
	else if (process_id > 0)
	{
		wait(0);
		close(pipe_fds[0]);
		close(pipe2_fds[1]);
		pipe_fds[0] = pipe2_fds[0];
		pipe_fds[1] = pipe2_fds[1];
	}
	else
		return (run_command(pipe_fds[0], pipe2_fds[1], command));
	return (0);
}

int	pipe_multiple_commands(int argc, char **argv, int *pipe_fds)
{
	int	command_i;

	command_i = 3;
	while (command_i < argc - 2)
	{
		pipe_to_pipe(pipe_fds, argv[command_i]);
		command_i++;
	}
	return (0);
}

void	pipe_commands(int argc, char **argv, int *file_fds)
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
		if (pipe_multiple_commands(argc, argv, pipe_fds) == -1)
			return ;
	}
	pipe_to_file(file_fds, pipe_fds, argv[argc - 2]);
}
