#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "libft.h"
# include "mlx.h"

/* PROGRAM MACROS */
# define W 119
# define S 115
# define D 100
# define A 97
# define RIGHT 65363
# define LEFT 65361
# define ESC 65307

# define TEX_SIZE 64
# define WIN_WIDTH 960 //640
# define WIN_HEIGHT 720 //480
# define TOLERANCE 0.25
# define MOVESPEED 0.1
# define ROTSPEED 0.075

# define MINIMAP_TILE_SIZE 10
# define MINIMAP_GRID_SIZE 20
# define MINIMAP_WALL_COLOR 0x1F1B1B
# define MINIMAP_PATH_COLOR 0x483B3A
# define MINIMAP_PLAYER_COLOR 0xAC8F7B

/* STRUCTURES */

typedef struct s_element
{
	int	i;
	int	j;
	int	end;
}	t_element;

typedef struct s_minimap
{
	int		tile_x;
	int		tile_y;
	int		screen_x;
	int		screen_y;
	int		offset_x;
	int		offset_y;
	int		map_x;
	int		map_y;
	int		color;
	char	map_tile;
}	t_minimap;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	dir_x;
	double	dir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_x;
	double	camera_x;
	double	wall_dist;
}	t_ray;

typedef struct s_player
{
	char	direction;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;

typedef struct s_map
{
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
}	t_map;

typedef struct s_texture_column
{
	int		x;
	int		y;
	int		index;
	double	pos;
	double	step;
}	t_texture_column;

typedef struct s_textures
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	unsigned long	hex_ceiling;
	unsigned long	hex_floor;
}	t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			**texture_tab;
	int			**pixels;
	t_map		mapinfo;
	t_player	player;
	t_textures	textures;
}	t_game;

/* FUNCTIONS */
/* INIT */
void	init_data(t_game *game);
void	init_img(t_img *img);
void	init_ray(t_ray *ray);
void	init_pixel_matrix(t_game *game);
void	start_mlx(t_game *game);

/* PARSING */
void	parse_arguments(t_game *game, int argc, char **argv);
void	init_player_direction(t_player *player);
int		parse_data(t_game *game, char **file);
int		parse_colors(t_textures *textures, char *line, int j);
int		parse_textures(t_textures *textures, char *line, int j);
int		parse_map(t_game *game, char **file, int i);
int		validate_textures(t_textures *textures);
int		validate_map(t_game *game, char **map);
int		validate_elements(t_game *game, char **map);
int		validate_after_map(t_map *map);

/* RENDER */
int		game_loop(t_game *game);
int		raycasting(t_game *game, t_player *player);
void	fill_textures(t_game *game);
void	render_frame(t_game *game);
void	compute_wall_projection(t_ray *ray, t_player *player);
void	paint_wall_column(t_game *game, t_ray *ray, int x);
void	draw_minimap(t_game *game, t_img *image);

/* PLAYER MOVEMENT */
void	get_input(t_game *game);
int		move_player(t_game *game);

/* FREE EXIT */
void	free_exit(t_game *game, int code);
void	free_tab(void **tab);
int		error(const char *str, int use_errno);

/* UTILS */
bool	is_cub_file(char *arg);
bool	is_xpm_file(char *arg);
char	*ft_strndup(const char *src, size_t n);

#endif
