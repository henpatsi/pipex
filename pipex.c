/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:51:47 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/07 16:13:31 by hpatsi           ###   ########.fr       */
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

// int	set_in_out(int in_fd, int out_fd)
// {
// 	if (dup2(in_fd, 0) == -1)
// 		return (-1);
// 	if (dup2(out_fd, 1) == -1)
// 		return (-1);
// 	return (1);
// }

// void	handle_forks(int process_id, int *file_fds, int *pipe_fds, char *command)
// {
// 	if (process_id == 0) // child process
// 	{
// 		close(pipe_fds[0]); // does not need pipe read end
// 		set_in_out(file_fds[0], pipe_fds[1]);
// 		run_command("grep 3");
// 	}
// 	if (process_id > 0) // parent process
// 	{
// 		close(pipe_fds[1]); // does not need pipe write end
// 		wait(NULL);
// 		set_in_out(pipe_fds[0], file_fds[1]);
// 		run_command("wc");
// 	}
// }

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
		if (command_i == 2) // first command
		{
			ft_putstr_fd("\n-----First command\n", 2);
			// close(pipe_fds[0]);
			dup2(file_fds[0], 0);
			dup2(pipe_fds[1], 1);
			// set_in_out(file_fds[0], pipe_fds[1]);
		}
		else if (command_i == argc - 2) // last command
		{
			ft_putstr_fd("\n-----Last command\n", 2);
			close(pipe_fds[1]);
			dup2(pipe_fds[0], 0);
			dup2(file_fds[1], 1);
			// set_in_out(pipe_fds[0], file_fds[1]);
		}
		else
		{
			ft_putstr_fd("\n-----Middle command\n", 2); // TODO CLOSE PIPE END FOR READING, OPEN AGAIN WHEN WRITING
			dup2(pipe_fds[0], 0);
			dup2(pipe_fds[1], 1);
			// set_in_out(pipe_fds[0], pipe_fds[1]);
		}

		process_id = fork();
		ft_putstr_fd("\nprocess created: ", 2);
		ft_putnbr_fd(process_id, 2);
		ft_putstr_fd("\n", 2);

		if (process_id < 0)
		{
			perror("fork failed");
			return (0);
		}
		else if (process_id > 0) // parent process
		{
			ft_putstr_fd("closing pipe on parent\n", 2);
			ft_putstr_fd("\nwaiting for child\ncommand_i = ", 2);
			ft_putnbr_fd(command_i, 2);
			ft_putstr_fd("\n", 2);

			waitpid(process_id, NULL, 0);
			
			ft_putstr_fd("\nchild finished\n", 2);
		}
		else if (process_id == 0) // child process
		{
			ft_putstr_fd("\nchild running\ncommand_i = ", 2);
			ft_putnbr_fd(command_i, 2);
			ft_putstr_fd("\nargc = ", 2);
			ft_putnbr_fd(argc, 2);
			ft_putstr_fd("\nargv[command] = ", 2);
			ft_putstr_fd(argv[command_i], 2);
			ft_putstr_fd("\n", 2);

			run_command(argv[command_i]);
		}
		command_i++;
	}
	return (0);
}
