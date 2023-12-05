/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:29:57 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/05 15:51:43 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	check_arguments(int argc, char **argv)
{
	int	infile_access;

	if (argc < 5)
	{
		ft_printf("not enough arguments\n");
		return (-1);
	}
	infile_access = access(argv[1], R_OK);
	if (infile_access == -1)
	{
		perror("access error reading from infile");
		return (-1);
	}
	return (0);
}