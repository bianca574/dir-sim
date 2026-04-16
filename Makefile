CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude

NAME = program

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

<<<<<<< HEAD
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
=======
main: premiereCommande.o main.o 
	gcc $(CFLAGS) -o main main.o premiereCommande.o

premiereCommande.o : dataNode.h premiereCommande.c premiereCommande.h
	gcc $(CFLAGS) -c premiereCommande.c

main.o: main.c dataNode.h premiereCommande.h
	gcc $(CFLAGS) -c main.c 
>>>>>>> 4159478 (premieres commandes : ls et mkdir)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
<<<<<<< HEAD
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
=======
	rm -f *.o main
>>>>>>> 4159478 (premieres commandes : ls et mkdir)
