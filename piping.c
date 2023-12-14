/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:23:00 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/14 14:16:41 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	run_command(int input_fd, int output_fd, char **command)
{
	if (dup2(input_fd, 0) == -1 || dup2(output_fd, 1) == -1)
		return (-1);
	return (execve(command[0], command, NULL));
}

int	file_to_pipe(int *file_fds, int *pipe_fds, char **command)
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

int	pipe_to_file(int *file_fds, int *pipe_fds, char **command)
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

int	pipe_to_pipe(int *pipe_fds, char **command)
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

void	pipe_commands(int *file_fds, char ***commands)
{
	int	pipe_fds[2];
	int	i;

	if (pipe(pipe_fds) < 0)
	{
		perror("pipe failed");
		return ;
	}
	i = 0;
	if (file_to_pipe(file_fds, pipe_fds, commands[i]) == -1)
		return ;
	i++;
	while (commands[i + 1] != 0)
	{
		pipe_to_pipe(pipe_fds, commands[i]);
		i++;
	}
	pipe_to_file(file_fds, pipe_fds, commands[i]);
}
