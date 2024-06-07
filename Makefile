NAME = GOL

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I./include -I$(RAYLIB_DIR)/include

ifeq ($(OS), Windows_NT)
	RAYLIB_DIR = ./raylib/raylib-5.0_win64_mingw-w64
	LDLIBS = $(RAYLIB_DIR)/lib/libraylib.a -lgdi32 -lwinmm
else
	RAYLIB_DIR = ./raylib/raylib-5.0_linux_amd64
	LDLIBS = $(RAYLIB_DIR)/lib/libraylib.a -lGL -lm
endif

SRC_DIR = ./src/
PATTERN_DIR = ./pattern/
OBJ_DIR = ./obj/

SRC_FILES = main.c
PATTERN_FILES = glider.c gospel_gun_glider.c blinker.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
PATTERN = $(addprefix $(PATTERN_DIR), $(PATTERN_FILES))

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC)) \
		$(patsubst $(PATTERN_DIR)%.c, $(OBJ_DIR)%.o, $(PATTERN)) \

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(PATTERN_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
ifeq ($(OS), Windows_NT)
	$(RM) $(NAME).exe
else
	$(RM) $(NAME)
endif

re: fclean all

run: $(NAME)
	./$(NAME)

.PHONY = all clean fclean re run
