#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// void put_multiple_pixel(t_data *img, void (my_mlx_pixel_put)(t_data *data, int x, int y, int color)))
// {
// 	while()
// 	{
// 		my_mlx_pixel_put(img, 5, 5, 0x00FF0000);
// 	}
// }