#include "cub3d.h"

static int	get_line_count(char *file)
{
	int		i;
	int		fd;
	int		line_count;
	char	buffer[1024];
	ssize_t	bytes_read;

	line_count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error("Error opening file", 1));
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		i = -1;
		while (++i < bytes_read)
			if (buffer[i] == '\n')
				line_count++;
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	if (bytes_read < 0)
		return (error("Error reading file", 1));
	close(fd);
	return (line_count);
}

static void	parse_file_helper(t_game *game, int fd)
{
	int		row;
	char	*line;

	line = get_next_line(fd);
	row = 0;
	while (line != NULL)
	{
		game->mapinfo.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!game->mapinfo.file[row])
		{
			free(line);
			error("Could not allocate memory", 1);
			return (free_tab((void **)game->mapinfo.file));
		}
		ft_strcpy(game->mapinfo.file[row], line);
		free(line);
		line = get_next_line(fd);
		row++;
	}
	game->mapinfo.file[row] = NULL;
}

static void	parse_file(t_game *game, char *file)
{
	int	fd;

	game->mapinfo.file = ft_calloc(get_line_count(file) + 1, sizeof(char *));
	if (!game->mapinfo.file)
	{
		error("Could not allocate memory", 1);
		return ;
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		error("Error opening file", 1);
		return ;
	}
	parse_file_helper(game, fd);
	close(fd);
}

void	parse_arguments(t_game *game, int argc, char **argv)
{
	if (argc != 2)
		free_exit(game, error("Try ./cub3d files/maps/good/[map_name]", 0));
	if (!is_cub_file(argv[1]))
		free_exit(game, 1);
	parse_file(game, argv[1]);
	if (parse_data(game, game->mapinfo.file) == 1)
		free_exit(game, 1);
	if (validate_map(game, game->map) == 1)
		free_exit(game, 1);
	init_player_direction(&game->player);
}
