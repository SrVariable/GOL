NAME = GOL

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I./ -I$(RAYLIB_DIR)/include
LDFLAGS = -L$(RAYLIB_DIR)
LDLIBS = -lraylib -lGL -lm

RAYLIB_DIR = ./raylib-5.0_linux_amd64/
RAYLIB = $(RAYLIB_DIR)/lib/libraylib.a

FILES = main.c

all: $(NAME)

$(NAME): $(RAYLIB) $(FILES)
	$(CC) $(FILES) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all

run: $(NAME)
	./$(NAME)

.PHONY = all clean fclean re run
