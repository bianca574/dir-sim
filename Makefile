CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC = src/main.c
OBJ = $(SRC:.c=.o)

program: $(OBJ)
	$(CC) $(CFLAGS) -o program $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f program

re: fclean program