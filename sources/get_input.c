#include "cub3d.h"

static int	quit_game(t_game *game)
{
	free_exit(game, 0);
	return (0);
}

int	mouse_move_handler(int x, int y, t_game *game)
{
	int	dead_zone_start;
	int	dead_zone_end;

	(void)y;
	dead_zone_start = WIN_WIDTH * 0.25;
	dead_zone_end = WIN_WIDTH * 0.75;
	if (x < dead_zone_start)
	{
		if (game->player.rotate > -1)
			game->player.rotate -= 1;
	}
	else if (x > dead_zone_end)
	{
		if (game->player.rotate < 1)
			game->player.rotate += 1;
	}
	else
		game->player.rotate = 0;
	return (0);
}

static int	key_release_handler(int key, t_game *game)
{
	if (key == W && game->player.move_y == 1)
		game->player.move_y = 0;
	if (key == S && game->player.move_y == -1)
		game->player.move_y = 0;
	if (key == D && game->player.move_x == 1)
		game->player.move_x = 0;
	if (key == A && game->player.move_x == -1)
		game->player.move_x = 0;
	if (key == RIGHT && game->player.rotate >= -1)
		game->player.rotate = 0;
	if (key == LEFT && game->player.rotate <= 1)
		game->player.rotate = 0;
	return (0);
}

static int	key_press_handler(int key, t_game *game)
{
	if (key == W)
		game->player.move_y = 1;
	if (key == S)
		game->player.move_y = -1;
	if (key == D)
		game->player.move_x = 1;
	if (key == A)
		game->player.move_x = -1;
	if (key == RIGHT)
		game->player.rotate += 1;
	if (key == LEFT)
		game->player.rotate -= 1;
	if (key == ESC)
		quit_game(game);
	return (0);
}

void	get_input(t_game *game)
{
	mlx_hook(game->win, 2, 1 << 0, key_press_handler, game);
	mlx_hook(game->win, 3, 1 << 1, key_release_handler, game);
	mlx_hook(game->win, 17, 0, quit_game, game);
	if (BONUS)
		mlx_hook(game->win, 6, 1L << 6, mouse_move_handler, game);
}
