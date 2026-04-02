#include "cub3d.h"

static int	parse_data_helper(t_game *game, char **file, int i, int j)
{
	if (file[i][j + 1] && ft_isprint(file[i][j + 1]) && \
		file[i][j + 1] != ' ' && !ft_isdigit(file[i][j]))
	{
		if (parse_textures(&game->textures, file[i], j) == 1)
			return (error("Invalid sprite texture(s)", 0));
	}
	else
	{
		if (parse_colors(&game->textures, file[i], j) == 1)
			return (error("Invalid ceiling/floor color(s)", 0));
	}
	return (0);
}

int	parse_data(t_game *game, char **file)
{
	int	i;
	int	j;

	i = -1;
	while (file[++i])
	{
		j = 0;
		while (ft_isspace(file[i][j]))
			j++;
		if (ft_isprint(file[i][j]) && \
			file[i][j] != ' ' && !ft_isdigit(file[i][j]))
		{
			if (parse_data_helper(game, file, i, j) == 1)
				return (1);
		}
		else if (ft_isdigit(file[i][j]))
		{
			if (validate_textures(&game->textures) == 1)
				return (1);
			if (parse_map(game, file, i) == 1)
				return (error("Map is wrong or incomplete", 0));
			return (0);
		}
	}
	return (0);
}
