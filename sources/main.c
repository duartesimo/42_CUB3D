#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_game	game;

	init_data(&game);
	parse_arguments(&game, argc, argv);
	start_mlx(&game);
	fill_textures(&game);
	render_frame(&game);
	get_input(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
