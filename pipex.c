/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:51:47 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/13 15:16:58 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_first_word(char *str)
{
	char	*word;
	int		i;

	while (*str != 0 && ft_isspace(*str))
		str++;
	i = 0;
	while (str[i] != 0 && !ft_isspace(str[i]))
		i++;
	word = ft_calloc(i + 1, 1);
	if (word == NULL)
		return (NULL);
	i = 0;
	while (str[i] != 0 && !ft_isspace(str[i]))
	{
		word[i] = str[i];
		i++;
	}
	return (word);
}

int	check_commands(int argc, char **argv)
{
	char	*command;
	int		i;

	i = 2;
	while (i < argc - 1)
	{
		command = get_first_word(argv[i]);
		
		i++;
	}
	return (0);
}

int	set_files(int argc, char **argv, int *file_fds)
{
	file_fds[0] = open(argv[1], O_RDONLY);
	if (file_fds[0] == -1)
	{
		perror(argv[1]);
		return (-1);
	}
	file_fds[1] = open(argv[argc - 1], O_RDWR | O_CREAT, 0666);
	if (file_fds[1] == -1)
	{
		close(file_fds[0]);
		perror(argv[argc - 1]);
		return (-1);
	}
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
	if (check_commands(argc, argv) == -1)
		return (0);
	if (set_files(argc, argv, file_fds) == -1)
		return (0);
	pipe_commands(argc, argv, file_fds);
	return (0);
}
