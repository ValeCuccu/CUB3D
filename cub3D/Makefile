# --- NOME DEL PROGRAMMA ---
NAME        = cub3D

# --- COLORI (Solo Verde e Rosso) ---
GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m

# --- COMPILATORE E FLAG ---
CC          = cc
# Nota: aggiunto -I./inc per dire al compilatore dove trovare i file .h
CFLAGS      = -Wall -Wextra -Werror -I./inc

# --- PATHS AGGIORNATI ---
# Le librerie ora sono dentro inc/
LIBFT_DIR   = inc/libft/
MLX_DIR     = inc/minilibx-linux/

# Aggiornati i flag di linking per puntare alle nuove directory
LDFLAGS     = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# --- SORGENTI AGGIORNATI (Aggiunto il prefisso src/) ---
# Il main ora è in src/
SRC_MAIN    = src/main.c

# Parte di Antonio (Parsing)
SRC_PARSING = src/parsing/line_checks.c \
              src/parsing/parse_color.c \
              src/parsing/parse_file.c \
              src/parsing/parse_map.c \
              src/parsing/parse_texture.c \
              src/parsing/utils.c \
              src/parsing/validation.c

# Parte Tua (Raycasting)
SRC_RAY     = src/raycasting-prova/init_engine.c \
              src/raycasting-prova/render.c \
              src/raycasting-prova/math_utils.c \
              src/raycasting-prova/utils.c \
			  src/raycasting-prova/movment.c \
			  src/raycasting-prova/ray_env.c

SRCS        = $(SRC_MAIN) $(SRC_PARSING) $(SRC_RAY)
OBJS        = $(SRCS:.c=.o)

# --- REGOLE (Nessuna modifica strutturale necessaria qui) ---

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR) > /dev/null
	@make -C $(MLX_DIR) > /dev/null
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ cub3D creato con successo!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ || (echo "$(RED)❌ Errore nella compilazione di $<$(RESET)" && exit 1)

clean:
	@make clean -C $(LIBFT_DIR) > /dev/null
	@rm -f $(OBJS)
	@echo "$(GREEN)🗑️  File oggetto rimossi.$(RESET)"

fclean: clean
	@make fclean -C $(LIBFT_DIR) > /dev/null
	@rm -f $(NAME)
	@echo "$(GREEN)🗑️  Eseguibile cub3D rimosso.$(RESET)"

re: fclean all

all: $(NAME)

bonus: all
	@echo "$(GREEN)✅ Bonus compilati (se presenti).$(RESET)"

.PHONY: all clean fclean re bonus