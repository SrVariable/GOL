NAME = GOL

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I./ -I$(RAYLIB_DIR)/include
ifneq ($(OS), Windows_NT)
	LDFLAGS = -L$(RAYLIB_DIR)
endif
ifeq ($(OS), Windows_NT)
	LDLIBS = -lraylib -lgdi32 -lwinmm
else
	LDLIBS = -lraylib -lGL -lm
endif

ifeq ($(OS), Windows_NT)
	RAYLIB_DIR = ./raylib/raylib-5.0_win64_mingw-w64/
else
	RAYLIB_DIR = ./raylib/raylib-5.0_linux_amd64/
endif
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
