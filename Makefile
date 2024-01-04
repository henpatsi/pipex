# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 08:46:34 by hpatsi            #+#    #+#              #
#    Updated: 2024/01/04 14:43:47 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = ./libft/libft.a

SOURCES = $(addprefix ./srcs/, pipex.c setup_commands.c setup_files.c piping.c helpers.c)

OBJECTS = $(SOURCES:.c=.o)

BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)

INCLUDES_DIR = ./includes/

CFLAGS += -Wall -Wextra -Werror -I $(INCLUDES_DIR)

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	cc $(CFLAGS) $(OBJECTS) $(LIBFT) -o pipex

$(OBJECTS): $(SOURCES)

$(LIBFT):
	make -C ./libft/

bonus: all

clean:
	make clean -C ./libft/
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

debug: clean $(DEBUG_OBJECTS) $(LIBFT)
	cc $(CFLAGS) -g $(SOURCES) $(LIBFT) -o pipex