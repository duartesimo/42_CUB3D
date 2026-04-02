#include "cub3d.h"

void	init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

static void	init_player(t_player *player)
{
	player->direction = '\0';
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->move_x = 0;
	player->move_y = 0;
	player->rotate = 0;
}

static void	init_map(t_map *map)
{
	map->file = NULL;
	map->height = 0;
	map->width = 0;
	map->index_end_of_map = 0;
}

static void	init_textures(t_textures *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->hex_floor = 0x0;
	textures->hex_ceiling = 0x0;
}

void	init_data(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	init_player(&game->player);
	init_textures(&game->textures);
	game->map = NULL;
	init_map(&game->mapinfo);
	game->pixels = NULL;
	game->texture_tab = NULL;
}
