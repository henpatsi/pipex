/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:36:55 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/05 13:30:46 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_strscpy(char **src, char **dst)
{
	int	i;

	i = 0;
	while (src[i] != 0)
	{
		dst[i] = ft_strdup(src[i]);
		if (dst[i] == NULL)
		{
			ft_strsfree(src);
			ft_strsfree(dst);
			return (-1);
		}
		i++;
	}
	dst[i] = 0;
	return (0);
}

char	**ft_strsadd(char **strs, char *str)
{
	char	**new_strs;
	int		i;

	i = 0;
	while (strs[i] != 0)
		i++;
	new_strs = malloc((i + 2) * sizeof(char *));
	if (new_strs == NULL)
	{
		ft_strsfree(strs);
		return (NULL);
	}
	if (ft_strscpy(strs, new_strs) == -1)
		return (NULL);
	ft_strsfree(strs);
	while (new_strs[i] != 0)
		i++;
	new_strs[i] = ft_strdup(str);
	if (new_strs[i] == NULL)
	{
		ft_strsfree(new_strs);
		return (NULL);
	}
	new_strs[++i] = 0;
	return (new_strs);
}
