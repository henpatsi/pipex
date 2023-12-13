/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:17:11 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/13 16:17:11 by hpatsi           ###   ########.fr       */
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

int check_command_path(char *path, char *command)
{
	char	*path_command;
	int		success;

	path_command = ft_strjoin(path, command);
	if (path_command == 0)
		return (0);
	if (access(path_command, X_OK) == 0)
		success = 1;
	else
		success = 0;
	free(path_command);
	return (success);
}

int	check_commands(int argc, char **argv)
{
	char	*command;
	int		i;

	i = 2;
	while (i < argc - 1)
	{
		command = get_first_word(argv[i]);
		if (command == 0)
			return (-1);
		if (!check_command_path("/bin/", command)
			&& !check_command_path("/usr/bin/", command))
		{
			ft_putstr_fd(argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			free(command);
			return (-1);
		}
		i++;
	}
	free(command);
	return (0);
}