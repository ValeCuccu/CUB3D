# --- COLORI ---
GREEN	= \033[0;32m
RED		= \033[0;31m
YELLOW	= \033[0;33m
RESET	= \033[0m

# --- CONFIGURAZIONE ---
NAME	= cub3D
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Iinc
RM		= rm -f

# --- PATHS ---
SRC_DIR	= src/
OBJ_DIR	= obj/

# Lista dei file (da aggiornare man mano che create i file .c)
SRCS	= $(SRC_DIR)main.c \
		  $(SRC_DIR)raycasting/engine.c \
		  $(SRC_DIR)parsing/parser.c \
		  $(SRC_DIR)utils/cleanup.c

OBJS	= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ Compilation successful: $(NAME) is ready!$(RESET)"

# Compilazione dei singoli file .o con creazione automatica delle cartelle
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ || (echo "$(RED)❌ Error compiling $<$(RESET)" && exit 1)
	@echo "$(YELLOW)Compiling: $<...$(RESET)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)Deleted object files.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Deleted executable $(NAME).$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus