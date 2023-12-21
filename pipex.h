/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:22:06 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/21 12:04:26 by hpatsi           ###   ########.fr       */
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
int		count_commands(char ***commands);
int		set_files(int argc, char **argv, int *file_fds);
char	***set_commands(int count, char **comm_strs, char *envp[]);
int		pipe_commands(int *file_fds, char ***commands, int **process_ids);

#endif