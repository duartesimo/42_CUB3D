#include "cub3d.h"

int	validate_after_map(t_map *map)
{
	int	i;
	int	j;

	i = map->index_end_of_map;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (!ft_isspace(map->file[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	validate_elements_helper(t_game *game, char **map, int i, int j)
{
	if (ft_strchr("NSEW", map[i][j]))
	{
		if (game->player.direction != '0')
			return (1);
		game->player.direction = map[i][j];
		game->player.pos_x = (double)j + 0.5;
		game->player.pos_y = (double)i + 0.5;
		map[i][j] = '0';
	}
	return (0);
}

int	validate_elements(t_game *game, char **map)
{
	t_element	elem;

	elem.i = 0;
	game->player.direction = '0';
	while (map[elem.i] != NULL)
	{
		elem.j = 0;
		elem.end = ft_strlen(map[elem.i]) - 1;
		while (ft_isspace(map[elem.i][elem.j]))
			elem.j++;
		while (elem.end >= 0 && ft_isspace(map[elem.i][elem.end]))
			elem.end--;
		while (elem.j <= elem.end)
		{
			if (!(ft_strchr("10NSEW", map[elem.i][elem.j])))
				return (error("Invalid character in map", 0));
			if (validate_elements_helper(game, map, elem.i, elem.j) == 1)
				return (error("Map has more than one player", 0));
			elem.j++;
		}
		elem.i++;
	}
	if (game->player.direction == '0')
		return (error("Map has no player", 0));
	return (0);
}
