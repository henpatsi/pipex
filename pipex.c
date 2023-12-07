/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:51:47 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/07 09:48:46 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
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
		perror(argv[0]);
	ft_strsfree(argv);
	return (1);
}

int	check_args(int argc, char **argv, int *file_fds)
{
	int	infile_fd;
	int	outfile_fd;

	if (argc < 5)
	{
		ft_printf("not enough arguments\n");
		return (-1);
	}
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

	if (check_args(argc, argv, file_fds) == -1)
		return (0);
	if (pipe(pipe_fds) < 0)
	{
		perror("pipe failed");
		return (0);
	}
	process_id = fork();
	if (process_id < 0)
	{
		perror("fork failed");
		return (0);
	}
	if (process_id == 0) // child process
	{
		close(pipe_fds[0]); // does not need pipe read end
		dup2(file_fds[0], 0); // change fd 0 from stdin to infile
		dup2(pipe_fds[1], 1); // change fd 1 from stdout to pipe write
		run_command(argv[2]);
	}
	if (process_id > 0) // parent process
	{
		close(pipe_fds[1]); // does not need pipe write end
		dup2(pipe_fds[0], 0); // change fd 0 from stdin to pipe read
		dup2(file_fds[1], 1); // change fd 1 from stdout to outfile
		wait(NULL);
		run_command(argv[3]);
	}
	return (0);
}
