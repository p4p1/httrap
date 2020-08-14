.SUFFIXES: .c .o

CC=				gcc
FLAGS=			-Wall -Wextra -Werror -I./include

NAME=			httrap

INCLUDE_DIR=	$(realpath ./include/)
INCLUDE=		$(INCLUDE_DIR)/config.h
SRC_DIR=		$(realpath ./src/)
SRC=			$(SRC_DIR)/main.c \
				$(SRC_DIR)/trap.c

OBJ=			$(SRC:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJ) $(INCLUDE)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

install:
	cp -r ./$(NAME) /usr/local/bin/$(NAME)
	mkdir -p /usr/local/share/man/man1
	cp -r httrap.1 /usr/local/share/man/man1/httrap.1
	chmod 644 /usr/local/share/man/man1/httrap.1

.c.o:
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean:			clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re install
