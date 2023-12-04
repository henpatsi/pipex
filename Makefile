# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 08:46:34 by hpatsi            #+#    #+#              #
#    Updated: 2023/12/04 10:55:27 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = ./libft/libft.a

SOURCES = pipex.c

OBJECTS = $(SOURCES:.c=.o)

INCLUDES_DIR = ./

CFLAGS += -Wall -Wextra -Werror -I $(INCLUDES_DIR)

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	cc $(CFLAGS) $(OBJECTS) $(LIBFT) -o pipex

$(OBJECTS): $(SOURCES)

$(LIBFT):
	make -C ./libft/

clean:
	make clean -C ./libft/
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

TEST_DIR = ./test_files/

test:
	< $(TEST_DIR)infile1 cat | wc -l > $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@echo ""
	./$(NAME) $(TEST_DIR)infile1 "cat" "wc -l" $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@echo ""

	< $(TEST_DIR)infile_noread cat | wc -l > $(TEST_DIR)outfile1
#	< $(TEST_DIR)infile1 cat | wc -l > $(TEST_DIR)outfile_nowrite
	@echo ""

	./$(NAME) $(TEST_DIR)infile_noread "cat" "wc -l" $(TEST_DIR)outfile1
	./$(NAME) $(TEST_DIR)infile1 "cat" "wc -l" $(TEST_DIR)outfile_nowrite