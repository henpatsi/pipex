# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 08:46:34 by hpatsi            #+#    #+#              #
#    Updated: 2023/12/14 14:18:51 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = ./libft/libft.a

SOURCES = pipex.c handle_input.c piping.c str_utils.c

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

NC='\033[0m'
GREEN='\033[0;32m'
LGREEN='\033[1;32m'

test: $(NAME)
	@printf ${GREEN}"\n\n----- VALID ALL -----\n\n"${NC}

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

	@printf ${GREEN}"\n\n----- NOT ENOUGH ARGS -----\n\n"${NC}
	./$(NAME) $(TEST_DIR)infile1 "cat" $(TEST_DIR)outfile1
	@echo ""

	@printf ${GREEN}"\n\n----- INVALID COMMAND -----\n"${NC}

	@printf ${LGREEN}"\n\n- First Command -\n"${NC}
	< $(TEST_DIR)infile1 nocommand | wc > $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	./$(NAME) $(TEST_DIR)infile1 "nocommand" "wc" $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	@printf ${LGREEN}"\n\n- Second Command -\n"${NC}
	< $(TEST_DIR)infile1 wc | nocommand > $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	./$(NAME) $(TEST_DIR)infile1 "wc" "nocommand" $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""
	
	@printf ${LGREEN}"\n\n- Both Commands -\n"${NC}
	< $(TEST_DIR)infile1 nocommand1 | nocommand2 > $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	./$(NAME) $(TEST_DIR)infile1 "nocommand1" "nocommand2" $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	@printf ${LGREEN}"\n\n- Invalid Command Args -\n"${NC}
	< $(TEST_DIR)infile1 wc | wc --noargs > $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	./$(NAME) $(TEST_DIR)infile1 "wc" "wc --noarg" $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	./$(NAME) $(TEST_DIR)infile1 "wc --noarg" "wc" $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	./$(NAME) $(TEST_DIR)infile1 "wc --noarg" "wc --noarg" $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	@printf ${GREEN}"\n\n----- INVALID FILES -----\n"${NC}

	@printf ${LGREEN}"\n\n- Input Read Restricted -\n"${NC}
	< $(TEST_DIR)infile_noread wc | wc > $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""
	
	./$(NAME) $(TEST_DIR)infile_noread "wc" "wc" $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	@printf ${LGREEN}"\n\n- Input Does Not Exist -\n"${NC}
	< $(TEST_DIR)infile_doesnotexist wc | wc > $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	./$(NAME) $(TEST_DIR)infile_doesnotexist "wc" "wc" $(TEST_DIR)outfile1
	cat $(TEST_DIR)outfile1
	@rm $(TEST_DIR)outfile1
	@echo ""

	@printf ${LGREEN}"\n\n- Output Write Restricted -\n"${NC}
	< $(TEST_DIR)infile1 cat | wc -l > $(TEST_DIR)outfile_nowrite
	@echo ""
	./$(NAME) $(TEST_DIR)infile1 "cat" "wc -l" $(TEST_DIR)outfile_nowrite
	@echo ""

	< $(TEST_DIR)infile1 nocommand1 | nocommand2 > $(TEST_DIR)outfile_nowrite
	@echo ""
	./pipex $(TEST_DIR)infile1 "nocommand1" "nocommand2" $(TEST_DIR)outfile_nowrite
	@echo ""

test_bonus: $(NAME)
	@printf ${GREEN}"\n\n----- VALID ALL -----\n\n"${NC}
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