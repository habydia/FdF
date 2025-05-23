#include "fdf.h"

static void	update_bounds(t_point *p, t_fdf *fdf, t_bounds *b)
{
	t_point	proj;

	proj = *p;
	project_point(&proj, fdf);
	if (proj.x < b->x_min)
		b->x_min = proj.x;
	if (proj.x > b->x_max)
		b->x_max = proj.x;
	if (proj.y < b->y_min)
		b->y_min = proj.y;
	if (proj.y > b->y_max)
		b->y_max = proj.y;
}

static void	get_bounds(t_map *map, t_fdf *fdf, t_bounds *b)
{
	int	i;
	int	j;

	b->x_min = WIN_WIDTH;
	b->x_max = 0;
	b->y_min = WIN_HEIGHT;
	b->y_max = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			update_bounds(&map->points[i][j], fdf, b);
			j++;
		}
		i++;
	}
}

static void	set_camera_zoom_offset(t_camera *c, t_bounds *b)
{
	double	zoom_x;
	double	zoom_y;
	double	margin;

	margin = 20;
	zoom_x = (WIN_WIDTH - 2 * margin) / (b->x_max - b->x_min);
	zoom_y = (WIN_HEIGHT - 2 * margin) / (b->y_max - b->y_min);
	c->zoom = zoom_x;
	if (zoom_y < zoom_x)
		c->zoom = zoom_y;
	c->x_offset = (WIN_WIDTH - (b->x_max + b->x_min) * c->zoom) / 2;
	c->y_offset = (WIN_HEIGHT - (b->y_max + b->y_min) * c->zoom) / 2;
}

void	fit_map_to_screen(t_camera *camera, t_map *map, t_fdf *fdf)
{
	t_bounds	b;

	camera->zoom = 1;
	camera->x_offset = 0;
	camera->y_offset = 0;
	get_bounds(map, fdf, &b);
	set_camera_zoom_offset(camera, &b);
}
