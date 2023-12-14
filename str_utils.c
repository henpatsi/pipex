/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:17:11 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/14 14:11:21 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	free_commands(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i] != 0)
	{
		ft_strsfree(commands[i]);
		i++;
	}
	free(commands);
	return (0);
}

// char	*get_first_word(char *str)
// {
// 	char	*word;
// 	int		i;

// 	while (*str != 0 && ft_isspace(*str))
// 		str++;
// 	i = 0;
// 	while (str[i] != 0 && !ft_isspace(str[i]))
// 		i++;
// 	word = ft_calloc(i + 1, 1);
// 	if (word == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] != 0 && !ft_isspace(str[i]))
// 	{
// 		word[i] = str[i];
// 		i++;
// 	}
// 	return (word);
// }
