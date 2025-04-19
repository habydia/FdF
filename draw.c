#include "fdf.h"

static void	draw_horizontal(t_fdf *fdf, int x, int y, t_point current)
{
	t_point	next;

	if (x + 1 < fdf->map->width)
	{
		next = fdf->map->points[y][x + 1];
		project_point(&next, fdf);
		draw_line(fdf->img, current, next);
	}
}

static void	draw_vertical(t_fdf *fdf, int x, int y, t_point current)
{
	t_point	next;

	if (y + 1 < fdf->map->height)
	{
		next = fdf->map->points[y + 1][x];
		project_point(&next, fdf);
		draw_line(fdf->img, current, next);
	}
}

static void	draw_map(t_fdf *fdf)
{
	int		x;
	int		y;
	t_point	current;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			current = fdf->map->points[y][x];
			project_point(&current, fdf);
			draw_horizontal(fdf, x, y, current);
			draw_vertical(fdf, x, y, current);
			x++;
		}
		y++;
	}
}

void	draw(t_fdf *fdf)
{
	ft_bzero(fdf->img->addr, WIN_WIDTH * WIN_HEIGHT * (fdf->img->bits_per_pixel / 8));
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
}
