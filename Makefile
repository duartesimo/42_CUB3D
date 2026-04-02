NAME = cub3D
CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address
CC = cc
RM = rm -rf
BONUS = 0

INCLUDES = -I ./includes/ -I ./includes/libft/ -I ./includes/minilibx-linux/
MINILIBX = includes/minilibx-linux/libmlx.a
LIBFT = includes/libft/libft.a

OBJ_DIR = objs/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

SRC_DIR = sources/
SRC =	main.c \
	check_map_1.c check_map_2.c \
	fill_textures.c \
	get_input.c \
	init_data.c \
	minimap.c \
	parse_arguments_1.c parse_arguments_2.c\
	parse_colors.c \
	parse_data.c \
	parse_map.c \
	parse_textures.c \
	player_move.c \
	raycasting_1.c raycasting_2.c \
	render_frame.c \
	utils_1.c utils_2.c

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) $(OBJ) -o $@ $(LIBFT) $(MINILIBX) $(INCLUDES) -lX11 -lXext -lm -lz -O3

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C includes/libft -s

$(MINILIBX):
	make -C includes/minilibx-linux -s

bonus: BONUS = 1
bonus: $(NAME)

clean:
	$(RM) $(OBJ_DIR)
	make -C includes/libft clean -s
	make -C includes/minilibx-linux clean -s

fclean: clean
	$(RM) $(NAME)
	make -C includes/libft fclean -s

re: fclean all

.PHONY: all re clean fclean bonus
