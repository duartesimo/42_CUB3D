#include "cub3d.h"

// Determines which texture to use for the wall based on the
// ray's direction and which side was hit.
// Vertical wall was hit. North or South Textures.
// Horizontal wall was hit. East or West Textures.
static void	get_texture(t_texture_column *tex_col, t_ray *ray)
{
	if (ray->side == 1)
	{
		if (ray->dir_y < 0)
			tex_col->index = 0;
		else
			tex_col->index = 1;
	}
	else
	{
		if (ray->dir_x > 0)
			tex_col->index = 2;
		else
			tex_col->index = 3;
	}
}

// Calculates the column of the texture to use for the current ray.
// Compute texture column based on wall_x.
// Hit left side of horizontal wall.
// Hit bottom side of vertical wall.
// ray->wall_x=0.75 TEX_SIZE=64, then tex_col->x=(int)(0.75 * 64)=48.
// the ray hit the wall near the right edge of the texture (column 48 of 64).
static void	get_texture_column(t_texture_column *tex_col, t_ray *ray)
{
	tex_col->x = (int)(ray->wall_x * TEX_SIZE);
	if (ray->side == 0 && ray->dir_x < 0)
		tex_col->x = TEX_SIZE - tex_col->x - 1;
	if (ray->side == 1 && ray->dir_y > 0)
		tex_col->x = TEX_SIZE - tex_col->x - 1;
}

// Paints wall column based on the calculated wall projection & texture.
// Determine which texture and column of the texture to use.
// How much to "step" vertically through texture for each pixel of wall
// Taller slice (line_height), smaller texture steps to spread smoothly
// Shorter slice will need larger steps
// Calculate the Initial Texture Position
// Draw the Wall Slice Pixel by Pixel
// tex_col.y calculates the corresponding row in the texture to sample
// tex_col.pos += tex_col.step moves to the next row in the texture.
// color is stored in the pixel buffer game->pixels[y][x] for rendering.
void	paint_wall_column(t_game *game, t_ray *ray, int x)
{
	int					y;
	int					color;
	t_texture_column	tex_col;

	get_texture(&tex_col, ray);
	get_texture_column(&tex_col, ray);
	tex_col.step = (double)TEX_SIZE / ray->line_height;
	tex_col.pos = (ray->draw_start - WIN_HEIGHT / 2 + \
		ray->line_height / 2) * tex_col.step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_col.y = (int)tex_col.pos & (TEX_SIZE - 1);
		tex_col.pos += tex_col.step;
		color = game->texture_tab[tex_col.index][tex_col.y \
			* TEX_SIZE + tex_col.x];
		game->pixels[y][x] = color;
		y++;
	}
}

// Ensures the vertical drawing bounds are within screen dimensions.
// Clip the start position to the top of the screen.
// Clip the end position to the bottom of the screen.
static void	clip_to_screen(int *start, int *end, int height)
{
	if (*start < 0)
		*start = 0;
	if (*end >= height)
		*end = height - 1;
}

// Calculates position, size of wall slice to be drawn for current ray
// Hit a horizontal wall. Compute perpendicular distance.
// Hit a vertical wall. Compute perpendicular distance.
// Calculate height wall slice on screen. (closer taller, further smaller)
// Starting + ending pixel position for the wall (centers it vertically)
// Ensure the drawing bounds are within the screen.
// Hit a horizontal wall. Determine the exact x-coordinate on the wall.
// Hit a vertical wall. Determine the exact y-coordinate on the wall.
// Isolate the fractional part to find the texture position.
void	compute_wall_projection(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(WIN_HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	clip_to_screen(&ray->draw_start, &ray->draw_end, WIN_HEIGHT);
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}
