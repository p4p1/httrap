.SUFFIXES: .c .o

CC=				gcc
FLAGS=			-Wall -Wextra -Werror -I./include -g3
LFLAGS=			-L./lib

NAME=			trap

INCLUDE_DIR=	$(realpath ./include/)
INCLUDE=		$(INCLUDE_DIR)/trap.h
SRC_DIR=		$(realpath ./src/)
SRC=			$(SRC_DIR)/main.c \
				$(SRC_DIR)/trap.c

OBJ=			$(SRC:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJ) $(INCLUDE)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LFLAGS)

install:
	cp -r ./$(NAME) /usr/local/bin/$(NAME)

.c.o:
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean:			clean
	@rm -rf $(NAME)
	@rm -rf lib/*.a

re: fclean all

.PHONY: clean fclean re install
