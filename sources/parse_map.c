#include "cub3d.h"

static void	change_space_into_wall(t_game *game)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (ft_isspace(game->map[i][j]))
			j++;
		len = ft_strlen(game->map[i]) - 1;
		while (game->map[i][j] && j < len)
		{
			if (game->map[i][j] == ' ')
				game->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

static int	fill_map_tab(t_map *mapinfo, char **map_tab, int index)
{
	int		i;
	int		j;

	i = 0;
	while (i < mapinfo->height)
	{
		j = 0;
		map_tab[i] = malloc(sizeof(char) * (mapinfo->width + 1));
		if (!map_tab[i])
			return (error("Could not allocate memory", 1));
		while (mapinfo->file[index][j] && mapinfo->file[index][j] != '\n')
		{
			map_tab[i][j] = mapinfo->file[index][j];
			j++;
		}
		while (j < mapinfo->width)
			map_tab[i][j++] = '\0';
		i++;
		index++;
	}
	map_tab[i] = NULL;
	return (0);
}

static int	find_biggest_len(t_map *map, int i)
{
	int	biggest_len;
	int	len;

	biggest_len = ft_strlen(map->file[i]);
	while (map->file[++i])
	{
		len = ft_strlen(map->file[i]);
		if (len > biggest_len)
			biggest_len = len;
	}
	return (biggest_len);
}

static int	count_map_lines(t_game *game, char **file, int i)
{
	int	initial_index;
	int	j;

	initial_index = i;
	while (file[i])
	{
		j = 0;
		while (ft_isspace(file[i][j]))
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	game->mapinfo.index_end_of_map = i;
	return (i - initial_index);
}

int	parse_map(t_game *game, char **file, int i)
{
	game->mapinfo.height = count_map_lines(game, file, i);
	game->mapinfo.width = find_biggest_len(&game->mapinfo, i);
	game->map = malloc(sizeof(char *) * (game->mapinfo.height + 1));
	if (!game->map)
		return (error("Could not allocate memory", 1));
	if (fill_map_tab(&game->mapinfo, game->map, i) == 1)
		return (1);
	change_space_into_wall(game);
	return (0);
}
