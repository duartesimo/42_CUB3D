#include "cub3d.h"

// Checks if the current ray's map position goes out of boundaries.
// Tolerance allows a small margin to not flag near-boundary values
// due to rounding issues or precision errors.
static int	is_out_of_bounds(t_game *game, t_ray *ray)
{
	return (ray->map_x < TOLERANCE || ray->map_y < TOLERANCE
		|| ray->map_x > game->mapinfo.width - (1.0 + TOLERANCE)
		|| ray->map_y > game->mapinfo.height - (1.0 + TOLERANCE));
}

// Uses DDA to trace the ray through the grid until it hits a wall(1).
// ray->side checks if it hits a vertical or horizontal wall (grid)
// Go next x-intersect. Adjust map grid x spot. Its a vertical hit (grid).
// Go next y-intersect. Adjust map grid y spot. Its a horizontal hit (grid).
// Stop if the ray goes out of bounds. // Stop when hitting an actual wall(1).
static void	perform_dda(t_game *game, t_ray *ray)
{
	while (1)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_out_of_bounds(game, ray))
			return ;
		if (game->map[ray->map_y][ray->map_x] > '0')
			break ;
	}
}

// Sets up DDA parameters to determine the step size and initial
// distances to the grid boundaries.
// Moving left. // Moving right.  // Moving up.  // Moving down.
// step_x, step_y: Which direction + or - ray should go along the X and Y axes
// sidedist_x, sidedist_y: How far ray needs, to reach the first X and Y grid
static void	setup_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
	}
}

// Initializes the ray's direction and related parameters for a single column.
// Map column(x) to camera plane coordinate (-1 to 1) left to right of player
// dir_x and dir_y represent the central direction/ray the player is facing
// plane_x and plane_y define the plane perpendicular to their direction
// Multiplying the plane values by camera_x shifts the ray to the left or right
// ray->map_x and ray->map_y track which grid cell the ray starts in (player)
// ray->deltadist_x and ray->deltadist_y precompute how far the ray must travel
// in each direction (X or Y) to cross from one grid line to the next.
// If dir_x large deltadist_x small, steep angle, so X grid crossings are closer
// If dir_y large deltadist_y small, shallow angle, Y grid crossings are closer
static void	setup_ray(int x, t_ray *ray, t_player *player)
{
	init_ray(ray);
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

// Main raycasting loop that iterates through all columns of the screen,
// tracing rays and determining wall projections.
// Iterate over each screen column.
// Configure the ray for the current column.
// Set up DDA parameters for grid traversal.
// Trace the ray through the grid.
// Calculate the wall's height and position on screen.
// Render the wall slice for the current column.
int	raycasting(t_game *game, t_player *player)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		setup_ray(x, &ray, player);
		setup_dda(&ray, player);
		perform_dda(game, &ray);
		compute_wall_projection(&ray, player);
		paint_wall_column(game, &ray, x);
		x++;
	}
	return (0);
}
