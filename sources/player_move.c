#include "cub3d.h"

// Rotates a 2D vector (x, y) by a given angle in radians.
static void	rotate_vector(double *x, double *y, double angle)
{
	double	old_x;

	old_x = *x;
	*x = *x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
}

// Rotates the player's direction and camera plane
// by a specified rotation direction (rotdir).
static void	rotate_player(t_game *game, double rotdir)
{
	double	rotspeed;

	rotspeed = ROTSPEED * rotdir;
	rotate_vector(&game->player.dir_x, &game->player.dir_y, rotspeed);
	rotate_vector(&game->player.plane_x, &game->player.plane_y, rotspeed);
}

// Checks whether the position (x, y) is valid.
// In bonus mode, the position must not overlap a wall. Checks map bounds.
static bool	is_valid_pos(t_game *game, double x, double y)
{
	if (BONUS)
	{
		if (game->map[(int)y][(int)x] != '1')
			return (true);
	}
	else
	{
		if (x >= 0.25 && x < game->mapinfo.width - 1.25 && \
		y >= 0.25 && y < game->mapinfo.height - 0.25)
		{
			return (true);
		}
	}
	return (false);
}

// Attempts to move the player along the given x and y axes. 
// Updates the player's position if the move is valid and returns moved or not.
static int	move_player_axis(t_game *game, double move_x, double move_y)
{
	int		moved;
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + move_x * MOVESPEED;
	new_y = game->player.pos_y + move_y * MOVESPEED;
	moved = 0;
	if (is_valid_pos(game, new_x, game->player.pos_y))
	{
		game->player.pos_x = new_x;
		moved = 1;
	}
	if (is_valid_pos(game, game->player.pos_x, new_y))
	{
		game->player.pos_y = new_y;
		moved = 1;
	}
	return (moved);
}

// Handles player movement and rotation based on input.
// Moves the player along x or y axes, or rotates the direction
// and camera plane if needed. Returns the total movement status.
int	move_player(t_game *game)
{
	int	moved;

	moved = 0;
	if (game->player.move_y)
		moved += move_player_axis(game, game->player.dir_x * \
			game->player.move_y, game->player.dir_y * game->player.move_y);
	if (game->player.move_x)
		moved += move_player_axis(game, -game->player.dir_y * \
			game->player.move_x, game->player.dir_x * game->player.move_x);
	if (game->player.rotate)
	{
		rotate_player(game, game->player.rotate);
		moved++;
	}
	return (moved);
}
