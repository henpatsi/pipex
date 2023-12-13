/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:22:06 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/13 11:55:46 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h> 

# include "libft.h"

void	pipe_commands(int argc, char **argv, int *file_fds);
int		run_command(int input_fd, int output_fd, char *command);

#endif