#include "cub3d.h"

static int	validate_walls_helper(char **map_tab, int i)
{
	int	j;

	j = 0;
	if (!map_tab[i])
		return (1);
	while (ft_isspace(map_tab[i][j]))
		j++;
	if (map_tab[i][j] != '1')
		return (1);
	while (map_tab[i][j])
	{
		if (!ft_isspace(map_tab[i][j]) && map_tab[i][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

static int	validate_walls(t_map *map, char **map_tab)
{
	int	i;
	int	fail;
	int	start;
	int	end;

	fail = 0;
	if (validate_walls_helper(map_tab, 0) == 1)
		fail = 1;
	i = 1;
	while (i < map->height - 1)
	{
		start = 0;
		end = ft_strlen(map_tab[i]) - 1;
		while (ft_isspace(map_tab[i][start]))
			start++;
		while (end >= 0 && ft_isspace(map_tab[i][end]))
			end--;
		if (map_tab[i][start] != '1' || map_tab[i][end] != '1')
			fail = 1;
		i++;
	}
	if (validate_walls_helper(map_tab, map->height - 1) == 1)
		fail = 1;
	return (fail);
}

int	validate_map(t_game *game, char **map)
{
	if (!game->map || game->mapinfo.height < 3)
		return (error("Missing map or map is too small", 0));
	if (validate_walls(&game->mapinfo, map) == 1)
		return (error("Map is not surrounded by walls", 0));
	if (validate_elements(game, map) == 1)
		return (1);
	if (game->player.direction == '0')
		return (error("Map has no player", 0));
	if (validate_after_map(&game->mapinfo) == 1)
		return (error("Map is not the last element", 0));
	return (0);
}
