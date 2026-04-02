#include "cub3d.h"

static int	parse_single_value(char **str)
{
	int	value;

	value = 0;
	while (ft_isspace(**str))
		(*str)++;
	if (!ft_isdigit(**str))
		return (-1);
	while (ft_isdigit(**str))
	{
		value = value * 10 + (**str - '0');
		(*str)++;
	}
	while (ft_isspace(**str))
		(*str)++;
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

static int	parse_rgb_line(char *line, unsigned long *color)
{
	int	r;
	int	g;
	int	b;

	while (ft_isspace(*line))
		line++;
	r = parse_single_value(&line);
	if (r == -1 || *line != ',')
		return (-1);
	line++;
	g = parse_single_value(&line);
	if (g == -1 || *line != ',')
		return (-1);
	line++;
	b = parse_single_value(&line);
	if (b == -1)
		return (-1);
	while (ft_isspace(*line))
		line++;
	if (*line != '\0')
		return (-1);
	*color = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (0);
}

int	parse_colors(t_textures *textures, char *line, int j)
{
	if (line[j] == 'C')
	{
		if (parse_rgb_line(line + j + 1, &textures->hex_ceiling) == -1)
			return (error("Invalid ceiling RGB color", 0));
	}
	else if (line[j] == 'F')
	{
		if (parse_rgb_line(line + j + 1, &textures->hex_floor) == -1)
			return (error("Invalid floor RGB color", 0));
	}
	else
		return (error("Invalid floor/ceiling identifier", 0));
	return (0);
}
