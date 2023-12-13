/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:51:47 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/13 11:55:48 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

	if (argc < 5)
	{
		ft_putstr_fd("not enough arguments\n", 2);
		return (0);
	}
	if (set_files(argc, argv, file_fds) == -1)
		return (0);
	pipe_commands(argc, argv, file_fds);
	return (0);
}
