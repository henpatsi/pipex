/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:51:47 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/05 15:55:34 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	print_strs(char **strs)
{
	int i;

	i = 0;
	while (strs[i] != 0)
	{
		ft_printf("%s, ", strs[i]);
		i++;
	}
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

int	run_first_command(char *command, char *infile)
{
	char	**argv;

	argv = ft_split(command, ' ');
	if (argv == NULL)
		return (0);
	argv = ft_strsadd(argv, infile);
	if (argv == NULL)
		return (0);
	print_strs(argv);
	if (run_command_path(argv, "/bin/") == -1
		&& run_command_path(argv, "/usr/bin/") == -1)
		perror("error running command");
	ft_strsfree(argv);
	return (1);
}

int	run_command(char *command)
{
	char	**argv;

	argv = ft_split(command, ' ');
	if (argv == NULL)
		return (0);
	print_strs(argv);
	if (argv == NULL)
		return (0);
	if (run_command_path(argv, "/bin/") == -1
		&& run_command_path(argv, "/usr/bin/") == -1)
		perror("error running command");
	ft_strsfree(argv);
	return (1);
}

int	main(int argc, char **argv)
{
	int		pipe_fds[2];
	pid_t	process_id;
	int		outfile_fd;

	if (check_arguments(argc, argv) == -1)
		exit (1);
	outfile_fd = open(argv[4], O_RDWR | O_CREAT, 0666);
	if (outfile_fd == -1)
	{
		perror("error with outfile");
		return (0);
	}

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
		dup2(pipe_fds[1], 1); // change fd 1 from stdout to pipe write
		//ft_printf("child running command: %s\n", argv[2]);
		run_first_command(argv[2], argv[1]);
	}
	if (process_id > 0) // parent process
	{
		close(pipe_fds[1]); // does not need pipe write end
		dup2(pipe_fds[0], 0); // change fd 0 from stdin to pipe read
		dup2(outfile_fd, 1); // change fd 1 from stdout to outfile
		wait(NULL);
		//ft_printf("parent running command: %s\n", argv[3]);
		run_command(argv[3]);
	}
	
	return (0);
}
