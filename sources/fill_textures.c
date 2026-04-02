#include "cub3d.h"

void	init_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

// Loads a texture from an XPM file and converts it into a 1D array of pixels.
// Utilizes MiniLibX's XPM loading function to read the image file, extracts
// the image data into a buffer, and then frees the MiniLibX image.
// game Pointer to the game structure containing MiniLibX's context.
// path File path to the XPM texture to be loaded.
// return Pointer to an allocated buffer containing the texture's pixel data.
static int	*xpm_to_img(t_game *game, char *path)
{
	int			width;
	int			height;
	int			*buffer;
	t_img		image;

	width = TEX_SIZE;
	height = TEX_SIZE;
	init_img(&image);
	image.img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (image.img == NULL)
		free_exit(game, error("Could not create mlx image", 0));
	image.addr = (int *)mlx_get_data_addr(image.img, &image.pixel_bits,
			&image.size_line, &image.endian);
	buffer = ft_calloc(1, sizeof * buffer * TEX_SIZE * TEX_SIZE);
	if (!buffer)
		free_exit(game, error("Could not allocate memory", 1));
	ft_memcpy(buffer, image.addr, TEX_SIZE * TEX_SIZE * sizeof(int));
	mlx_destroy_image(game->mlx, image.img);
	return (buffer);
}

//fix to 4 and fix the frees at the end
//'The problem likely lies in how you're freeing the data->textures'
void	fill_textures(t_game *game)
{
	game->texture_tab = ft_calloc(5, sizeof * game->texture_tab);
	if (!game->texture_tab)
		free_exit(game, error("Could not allocate memory", 1));
	game->texture_tab[0] = xpm_to_img(game, game->textures.north);
	game->texture_tab[1] = xpm_to_img(game, game->textures.south);
	game->texture_tab[2] = xpm_to_img(game, game->textures.east);
	game->texture_tab[3] = xpm_to_img(game, game->textures.west);
}

// Initializes the pixel matrix that represents the game's screen.
// Allocates memory for a 2D array of pixels,
// with dimensions matching the screen size.
// Frees any previously allocated memory for the pixel matrix
// before reinitializing.
// game Pointer to the game structure containing the pixel matrix.
void	init_pixel_matrix(t_game *game)
{
	int	i;

	if (game->pixels)
		free_tab((void **)game->pixels);
	game->pixels = ft_calloc(WIN_HEIGHT + 1, sizeof * game->pixels);
	if (!game->pixels)
		free_exit(game, error("Could not allocate memory", 1));
	i = 0;
	while (i < WIN_HEIGHT)
	{
		game->pixels[i] = ft_calloc(WIN_WIDTH + 1, sizeof * game->pixels);
		if (!game->pixels[i])
			free_exit(game, error("Could not allocate memory", 1));
		i++;
	}
}
