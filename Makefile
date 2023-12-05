# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 08:46:34 by hpatsi            #+#    #+#              #
#    Updated: 2023/12/05 13:31:59 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = ./libft/libft.a

SOURCES = pipex.c str_utils.c check_args.c

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

debug: clean $(OBJECTS) $(LIBFT)
	cc $(CFLAGS) -g $(SOURCES) $(LIBFT) -o pipex

TEST_DIR = ./test_files/

test: $(NAME)
	@echo "\n--- VALID ALL ---"
	< $(TEST_DIR)infile1 cat | wc -l > $(TEST_DIR)outfile1
	@echo ""
	./$(NAME) $(TEST_DIR)infile1 "cat" "wc -l" $(TEST_DIR)outfile1
	@echo ""

	@echo "\n--- INVALID COMMAND ---"
	< $(TEST_DIR)infile1 nocommand | wc -l > $(TEST_DIR)outfile1
	@echo ""
	./$(NAME) $(TEST_DIR)infile1 "nocommand" "wc -l" $(TEST_DIR)outfile1
	@echo ""

	< $(TEST_DIR)infile1 cat | nocommand > $(TEST_DIR)outfile1
	@echo ""
	./$(NAME) $(TEST_DIR)infile1 "cat" "nocommand" $(TEST_DIR)outfile1
	@echo ""
	
	< $(TEST_DIR)infile1 nocommand | nocommand > $(TEST_DIR)outfile1
	@echo ""
	./$(NAME) $(TEST_DIR)infile1 "nocommand" "nocommand" $(TEST_DIR)outfile1
	@echo ""

	@echo "\n--- INVALID INPUT ---"
	< $(TEST_DIR)infile_noread cat | wc -l > $(TEST_DIR)outfile1
	@echo ""
	./$(NAME) $(TEST_DIR)infile_noread "cat" "wc -l" $(TEST_DIR)outfile1
	@echo ""

	@echo "\n--- INVALID OUTPUT ---"
	./$(NAME) $(TEST_DIR)infile1 "cat" "wc -l" $(TEST_DIR)outfile_nowrite
	@echo ""
	< $(TEST_DIR)infile1 cat | wc -l > $(TEST_DIR)outfile_nowrite
	@echo ""