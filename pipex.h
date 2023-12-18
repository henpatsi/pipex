/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:22:06 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/14 14:56:36 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h> 
# include <sys/errno.h>

# include "libft.h"

int		ft_strsfree(char **strs);
int		free_commands(char ***commands);

int		set_files(int argc, char **argv, int *file_fds);
char	***setup_commands(int command_count, char **argv_commands, int *ec_ptr, char **paths);

void	pipe_commands(int *file_fds, char ***commands);

#endif