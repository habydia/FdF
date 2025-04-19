#include "fdf.h"

static void	get_bounds(t_map *map, t_fdf *fdf,
		double *x_min, double *x_max, double *y_min, double *y_max)
{
	int		i;
	int		j;
	t_point	p;

	*x_min = WIN_WIDTH;
	*x_max = 0;
	*y_min = WIN_HEIGHT;
	*y_max = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			p = map->points[i][j];
			project_point(&p, fdf);
			if (p.x < *x_min)
				*x_min = p.x;
			if (p.x > *x_max)
				*x_max = p.x;
			if (p.y < *y_min)
				*y_min = p.y;
			if (p.y > *y_max)
				*y_max = p.y;
			j++;
		}
		i++;
	}
}

static void	set_camera_zoom_offset(t_camera *camera,
		double x_min, double x_max, double y_min, double y_max)
{
	double	zoom_x;
	double	zoom_y;
	double	margin;

	margin = 20;
	zoom_x = (WIN_WIDTH - 2 * margin) / (x_max - x_min);
	zoom_y = (WIN_HEIGHT - 2 * margin) / (y_max - y_min);
	camera->zoom = zoom_x;
	if (zoom_y < zoom_x)
		camera->zoom = zoom_y;
	camera->x_offset = (WIN_WIDTH - (x_max + x_min) * camera->zoom) / 2;
	camera->y_offset = (WIN_HEIGHT - (y_max + y_min) * camera->zoom) / 2;
}

void	fit_map_to_screen(t_camera *camera, t_map *map, t_fdf *fdf)
{
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;

	camera->zoom = 1;
	camera->x_offset = 0;
	camera->y_offset = 0;
	get_bounds(map, fdf, &x_min, &x_max, &y_min, &y_max);
	set_camera_zoom_offset(camera, x_min, x_max, y_min, y_max);
}
