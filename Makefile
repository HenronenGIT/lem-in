CYELLOW=\033[0;33m
CEND=\033[0m
CGREEN=\033[0;32m

CC = gcc
NAME = lem-in
FLAGS = -Wall -Wextra -g #-fsanitize=address

SRC_DIR = ./src/
SRC_FILES = main.c \
			vector_1.c \
			vector_2.c \
			read_rooms.c \
			read_links.c \
			array_hashing.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = ./obj/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

INC_DIR = ./includes/
INC_FILES = lem_in.h
INC = $(addprefix $(INC_DIR), $(INC_FILES))

# LIBPRINT_DIR = libftprintf/
# LIBPRINT_LIB = libftprintf.a
# LIBPRINT = $(addprefix $(LIBPRINT_DIR), $(LIBPRINT_LIB))
LIBPRINT_DIR = libft/
LIBPRINT_LIB = libft.a
LIBPRINT = $(addprefix $(LIBPRINT_DIR), $(LIBPRINT_LIB))

all : $(NAME)

$(NAME): $(OBJ) $(INC)
	@make -C $(LIBPRINT_DIR)
	@echo "$(CYELLOW)Compiling $(NAME)$(CEND)"
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ) -I libft/includes/ -I ./includes/ -L. $(LIBPRINT)
	@echo "$(CGREEN)OK$(CEND)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

clean :
	@make -C $(LIBPRINT_DIR) clean
	@echo "$(CYELLOW)Removing $(NAME) object folder$(CEND)"
	@rm -rf $(OBJ_DIR)
	@echo "$(CGREEN)OK$(CEND)"

fclean : clean
	@make -C $(LIBPRINT_DIR) fclean
	@echo "$(CYELLOW)Removing $(NAME)$(CEND)"
	@rm -rf $(NAME)
	@echo "$(CGREEN)OK$(CEND)"

#* Easier way to run and test program
run:
	./lem-in < ./eval_tests/test_maps/cnysten_tricky.map 
re : fclean all clean all
