#include "cub3d.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	len;
	char	*copy;

	i = 0;
	len = 0;
	while (len < n && src[len])
		len++;
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	while (i < len)
	{
		copy[i] = src[i];
		i++;
	}
	copy[len] = '\0';
	return (copy);
}

int	error(const char *str, int use_errno)
{
	if (use_errno)
		perror(str);
	else
		printf("Error: %s\n", str);
	return (EXIT_FAILURE);
}

void	free_tab(void **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	free_data(t_game *game)
{
	if (game->texture_tab)
		free_tab((void **)game->texture_tab);
	if (game->pixels)
		free_tab((void **)game->pixels);
	if (game->textures.north)
		free(game->textures.north);
	if (game->textures.south)
		free(game->textures.south);
	if (game->textures.east)
		free(game->textures.east);
	if (game->textures.west)
		free(game->textures.west);
	if (game->mapinfo.file)
		free_tab((void **)game->mapinfo.file);
	if (game->map)
		free_tab((void **)game->map);
}

void	free_exit(t_game *game, int code)
{
	if (!game)
		exit(code);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		mlx_loop_end(game->mlx);
		free(game->mlx);
	}
	free_data(game);
	exit(code);
}
