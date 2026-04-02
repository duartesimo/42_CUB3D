#include "cub3d.h"

static int	validate_texture_file(const char *file_path)
{
	if (access(file_path, F_OK) == -1)
	{
		error("Texture file does not exist", 0);
		return (1);
	}
	return (0);
}

int	validate_textures(t_textures *textures)
{
	if (!textures->north || !textures->south || \
		!textures->west || !textures->east)
		return (error("Missing texture(s)", 0));
	if (validate_texture_file(textures->north) || \
		validate_texture_file(textures->south) || \
		validate_texture_file(textures->west) || \
		validate_texture_file(textures->east))
		return (error("One or more texture files are missing or invalid", 0));
	if (!textures->hex_floor || !textures->hex_ceiling)
		return (error("Missing color(s)", 0));
	return (0);
}

static char	*get_texture_path(char *line, int j)
{
	char	*start;
	char	*end;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	start = &line[j];
	while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '\n')
		j++;
	end = &line[j];
	path = ft_strndup(start, end - start);
	if (!path)
	{
		error("Memory allocation failed", 1);
		return (NULL);
	}
	return (path);
}

int	parse_textures(t_textures *textures, char *line, int j)
{
	char	**texture_ptr;

	texture_ptr = NULL;
	if (line[j + 2] && ft_isprint(line[j + 2]) && line[j + 2] != ' ')
		return (1);
	if (ft_strncmp(&line[j], "NO", 2) == 0)
		texture_ptr = &textures->north;
	else if (ft_strncmp(&line[j], "SO", 2) == 0)
		texture_ptr = &textures->south;
	else if (ft_strncmp(&line[j], "WE", 2) == 0)
		texture_ptr = &textures->west;
	else if (ft_strncmp(&line[j], "EA", 2) == 0)
		texture_ptr = &textures->east;
	if (texture_ptr && !(*texture_ptr))
	{
		*texture_ptr = get_texture_path(line, j + 2);
		if (*texture_ptr == NULL || !is_xpm_file(*texture_ptr))
			return (1);
		if (validate_texture_file(*texture_ptr) == 1)
			return (1);
		return (0);
	}
	return (1);
}
