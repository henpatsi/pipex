# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 08:46:34 by hpatsi            #+#    #+#              #
#    Updated: 2023/12/13 11:52:21 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = ./libft/libft.a

SOURCES = pipex.c piping.c commands.c

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

debug: clean $(DEBUG_OBJECTS) $(LIBFT)
	cc $(CFLAGS) -g $(SOURCES) $(LIBFT) -o pipex

TEST_DIR = ./test_files/

test: $(NAME)
	@echo "\n\n--- VALID ALL ---\n"
	< $(TEST_DIR)infile1 wc | grep 3 > $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	./$(NAME) $(TEST_DIR)infile1 "wc" "grep 3" $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	< $(TEST_DIR)infile1 grep 3 | wc > $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""
	./$(NAME) $(TEST_DIR)infile1 "grep 3" "wc" $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	@echo "\n\n--- INVALID COMMAND ---\n"
	< $(TEST_DIR)infile1 nocommand | wc -l > $(TEST_DIR)outfile1
	@echo ""
	./$(NAME) $(TEST_DIR)infile1 "nocommand" "wc -l" $(TEST_DIR)outfile1
	@echo ""

#	< $(TEST_DIR)infile1 cat | nocommand > $(TEST_DIR)outfile1
#	@echo ""
#	./$(NAME) $(TEST_DIR)infile1 "cat" "nocommand" $(TEST_DIR)outfile1
#	@echo ""
	
#	< $(TEST_DIR)infile1 nocommand | nocommand > $(TEST_DIR)outfile1
#	@echo ""
#	./$(NAME) $(TEST_DIR)infile1 "nocommand" "nocommand" $(TEST_DIR)outfile1
#	@echo ""

	@echo "\n\n\n--- INVALID INPUT ---\n"
	< $(TEST_DIR)infile_noread cat | wc -l > $(TEST_DIR)outfile1
	@echo ""
	./$(NAME) $(TEST_DIR)infile_noread "cat" "wc -l" $(TEST_DIR)outfile1
	@echo ""

	@echo "\n\n--- INVALID OUTPUT ---\n"
#	< $(TEST_DIR)infile1 cat | wc -l > $(TEST_DIR)outfile_nowrite
#	@echo ""
	./$(NAME) $(TEST_DIR)infile1 "cat" "wc -l" $(TEST_DIR)outfile_nowrite
	@echo ""

	@echo "\n\n--- NOT ENOUGH ARGS ---\n"
	./$(NAME) $(TEST_DIR)infile1 "cat" $(TEST_DIR)outfile_nowrite
	@echo ""

test_bonus: $(NAME)
	@echo "\n\n--- VALID ALL ---\n"
	< $(TEST_DIR)infile1 grep 3 | wc | wc | tr -d 3 > $(TEST_DIR)outfile1
	@echo ""
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	./pipex $(TEST_DIR)infile1 "grep 3" "wc" "wc" "tr -d 3" $(TEST_DIR)outfile1
	@echo ""
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""