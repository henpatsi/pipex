/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:51:47 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/04 10:51:34 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int free_strs(char **strs)
{
	int i;

	i = 0;
	while (strs[i] != 0)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (0);
}

char	**add_to_strs(char **strs, char *str)
{
	char **new_strs;
	int i;

	i = 0;
	while (strs[i] != 0)
		i++;
	new_strs = malloc((i + 1) * sizeof(char *));
	if (new_strs == 0)
		return (0);
	i = 0;
	while (strs[i] != 0)
	{
		new_strs[i] = strs[i];
		i++;
	}
	free(strs);
	new_strs[i] = str;
	i++;
	new_strs[i] = 0;
	return (new_strs);
}

int	run_command(char *command_str, char *infile)
{
	static char **argv;
	static char *command;

	argv = ft_split(command_str, ' ');
	if (argv == 0)
		return (0);
	if (infile != 0)
	{
		argv = add_to_strs(argv, infile);
		if (argv == 0)
			return (0);
	}
	command = ft_strjoin("/bin/", argv[0]);
	if (command == 0)
		return (free_strs(argv));
	execve(command, argv, NULL);
	free(command);
	free_strs(argv);
	return (1);
}

int	main(int argc, char **argv)
{
	int infile_access;

	if (argc < 5)
	{
		ft_printf("Not enough arguments\n");
		return (0);
	}
	infile_access = access(argv[1], R_OK);
	if (infile_access == -1)
	{
		perror("Error opening infile");
		return (0);
	}
	// outfile_fd = open(argv[argc - 1], O_CREAT, O_RDWR);
	// if (outfile_fd == -1)
	// {
	// 	perror("Error opening outfile");
	// 	return (0);
	// }

	run_command(argv[2], argv[1]);
}
