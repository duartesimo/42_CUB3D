#include "cub3d.h"

void	start_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		free_exit(game, error("Could not start mlx", 0));
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game->win)
		free_exit(game, error("Could not create mlx window", 0));
	if (BONUS)
		mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

int	game_loop(t_game *game)
{
	int	moved;

	moved = move_player(game);
	if (moved == 0)
		return (0);
	render_frame(game);
	return (0);
}

static bool	has_extension(char *arg, const char *ext)
{
	size_t	len;
	size_t	ext_len;

	len = ft_strlen(arg);
	ext_len = ft_strlen(ext);
	if (len < ext_len + 1)
		return (false);
	return (ft_strncmp(arg + len - ext_len, ext, ext_len) == 0
		&& arg[len - ext_len - 1] == '.');
}

bool	is_cub_file(char *arg)
{
	if (!has_extension(arg, "cub"))
	{
		error("Not a .cub file", 0);
		return (false);
	}
	return (true);
}

bool	is_xpm_file(char *arg)
{
	if (!has_extension(arg, "xpm"))
	{
		error("Not an .xpm file", 0);
		return (false);
	}
	return (true);
}
