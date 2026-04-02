#include "cub3d.h"

// Draws a single pixel at the specified (x, y) position
// in the image with the given color. Ensures pixel inbounds.
static void	draw_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		pixel = y * (image->size_line / 4) + x;
		image->addr[pixel] = color;
	}
}

// Draws a square on the image at the minimap coordinates
// specified in the t_minimap struct. Square is a single tile
static void	draw_square(t_img *image, t_minimap *mini)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_TILE_SIZE)
	{
		j = 0;
		while (j < MINIMAP_TILE_SIZE)
		{
			draw_pixel(image, mini->screen_x + \
				j, mini->screen_y + i, mini->color);
			j++;
		}
		i++;
	}
}

// Processes and draws a single minimap tile based on its map
// coordinates, screen position, and type.
// Map coordinates of the tile relative to the minimap grid.
// Ensure the tile coordinates are within the bounds of the map.
// Screen coordinates for the current tile on the minimap.
// Determine the tile type and assign its color (wall, path, or player).
static void	draw_minimap_helper(t_game *game, t_img *image, t_minimap *mini)
{
	mini->map_x = mini->offset_x + mini->tile_x;
	mini->map_y = mini->offset_y + mini->tile_y;
	if (mini->map_x < 0 || mini->map_x >= game->mapinfo.width \
		|| mini->map_y < 0 || mini->map_y >= game->mapinfo.height)
		return ;
	mini->screen_x = WIN_WIDTH - (MINIMAP_GRID_SIZE * MINIMAP_TILE_SIZE) \
		+ (mini->tile_x * MINIMAP_TILE_SIZE);
	mini->screen_y = WIN_HEIGHT - (MINIMAP_GRID_SIZE * MINIMAP_TILE_SIZE) \
		+ (mini->tile_y * MINIMAP_TILE_SIZE);
	mini->map_tile = game->map[mini->map_y][mini->map_x];
	if (mini->map_tile == '1')
		mini->color = MINIMAP_WALL_COLOR;
	else
		mini->color = MINIMAP_PATH_COLOR;
	if ((int)game->player.pos_x == mini->map_x && \
		(int)game->player.pos_y == mini->map_y)
		mini->color = MINIMAP_PLAYER_COLOR;
	draw_square(image, mini);
}

// Ensures the player’s position is in center of the minimap by shifting view.
// Center the minimap around the player.
// Clamp to the beginning of the map.
// Clamp to the end of the map.
static int	get_minimap_offset(int player_pos, int map_size, int grid_size)
{
	int	offset;

	offset = player_pos - grid_size / 2;
	if (offset < 0)
		offset = 0;
	if (offset + grid_size > map_size)
		offset = map_size - grid_size;
	return (offset);
}

// Calculate offsets to center the minimap around the player position.
// Iterates through the minimap grid to render each tile.
void	draw_minimap(t_game *game, t_img *image)
{
	t_minimap	mini;

	mini.offset_x = get_minimap_offset((int)game->player.pos_x, \
		game->mapinfo.width, MINIMAP_GRID_SIZE);
	mini.offset_y = get_minimap_offset((int)game->player.pos_y, \
		game->mapinfo.height, MINIMAP_GRID_SIZE);
	mini.tile_y = 0;
	while (mini.tile_y < MINIMAP_GRID_SIZE)
	{
		mini.tile_x = 0;
		while (mini.tile_x < MINIMAP_GRID_SIZE)
		{
			draw_minimap_helper(game, image, &mini);
			mini.tile_x++;
		}
		mini.tile_y++;
	}
}
