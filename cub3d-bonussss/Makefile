NAME        = cub3D_bonus

GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I./inc

LIBFT_DIR   = inc/libft/
MLX_DIR     = inc/minilibx-linux/

LDFLAGS     = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# ==========================================
# FILE SORGENTE (Tutti inclusi)
# ==========================================
# NOTA: Assicurati che src/main_test.c sia il file corretto. 
# Se l'hai rinominato in main.c, cambialo qui sotto.
SRC_MAIN    = src/main_test.c

SRC_PARSING = src/parsing/line_checks.c \
              src/parsing/parse_color.c \
              src/parsing/parse_file.c \
              src/parsing/parse_map.c \
              src/parsing/parse_texture.c \
              src/parsing/utils.c \
              src/parsing/validation.c \
              src/parsing/validation2.c

SRC_RAY     = src/raycasting/init_engine.c \
              src/raycasting/render.c \
              src/raycasting/general_utils.c \
              src/raycasting/dda.c \
              src/raycasting/key_utils.c \
              src/raycasting/minimap_utils.c \
              src/raycasting/raycasting.c \
              src/raycasting/textures_utils.c \
              src/raycasting/mouse_env.c

SRCS        = $(SRC_MAIN) $(SRC_PARSING) $(SRC_RAY)
OBJS        = $(SRCS:.c=.o)

# ==========================================
# REGOLE
# ==========================================
all: $(NAME)

# Compila tutti i file in un eseguibile chiamato cub3D
$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR) > /dev/null
	@make -C $(MLX_DIR) > /dev/null
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ cub3D_bonus compilato con successo!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ || (echo "$(RED)❌ Errore nella compilazione di $<$(RESET)" && exit 1)

clean:
	@make clean -C $(LIBFT_DIR) > /dev/null
	@rm -f $(OBJS)
	@echo "$(GREEN)🗑️  File oggetto rimossi.$(RESET)"

fclean: clean
	@make fclean -C $(LIBFT_DIR) > /dev/null
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "$(GREEN)🗑️  Eseguibili rimossi.$(RESET)"

re: fclean all

bonus: $(NAME)

$(NAME_BONUS): $(OBJS)
	@make -C $(LIBFT_DIR) > /dev/null
	@make -C $(MLX_DIR) > /dev/null
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME_BONUS)
	@echo "$(GREEN)🌟 cub3D_bonus compilato con successo!$(RESET)"

.PHONY: all clean fclean re bonus