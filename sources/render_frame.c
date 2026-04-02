#include "cub3d.h"

// Draws a single pixel at (x, y) in the given image with the specified color.
// This formula calculates the position of a specific pixel in the image buffer
// (a 1D array), based on its (x, y), divide by 4 because int = 4 bytes
static void	draw_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		pixel = y * (image->size_line / 4) + x;
		image->addr[pixel] = color;
	}
}

// Draws walls on '1' on the image based on the calculated pixels raycasting.
static void	draw_walls(t_game *game, t_img *image)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			if (game->pixels[y][x] > 0)
				draw_pixel(image, x, y, game->pixels[y][x]);
			y++;
		}
		x++;
	}
}

// Fills the entire screen with the ceiling color on the top half
// and the floor color on the bottom half.
static void	draw_floor_ceiling(t_img *image, int ceiling_color, int floor_color)
{
	int	y;
	int	color;
	int	x;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		if (y < WIN_HEIGHT / 2)
			color = ceiling_color;
		else
			color = floor_color;
		x = -1;
		while (++x < WIN_WIDTH)
			draw_pixel(image, x, y, color);
	}
}

// Initializes an image buffer to store pixel data for rendering a frame.
static void	init_image_buffer(t_game *game, t_img *image, int width, int height)
{
	init_img(image);
	image->img = mlx_new_image(game->mlx, width, height);
	if (image->img == NULL)
		free_exit(game, error("Could not create mlx image", 0));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
}

// Clears the pixel matrix for the new frame.
// Calculates wall and object projections.
// Game pixels contains color values for the walls
// Sets up the image buffer. Draws the floor, ceiling, walls, minimap
// Displays the frame. Cleans up the image buffer.
void	render_frame(t_game *game)
{
	t_img	image;

	init_pixel_matrix(game);
	raycasting(game, &game->player);
	init_image_buffer(game, &image, WIN_WIDTH, WIN_HEIGHT);
	draw_floor_ceiling(&image, game->textures.hex_ceiling, \
		game->textures.hex_floor);
	draw_walls(game, &image);
	if (BONUS)
		draw_minimap(game, &image);
	mlx_put_image_to_window(game->mlx, game->win, image.img, 0, 0);
	mlx_destroy_image(game->mlx, image.img);
}
