#include "fdf.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

static void	rotate_point(int *x, int *y, int *z, t_camera *camera)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	prev_x = *x;
	prev_y = *y;
	prev_z = *z;
	// Rotation autour de l'axe X
	*y = prev_y * cos(camera->alpha) + prev_z * sin(camera->alpha);
	*z = -prev_y * sin(camera->alpha) + prev_z * cos(camera->alpha);
	prev_y = *y;
	prev_z = *z;
	// Rotation autour de l'axe Y
	*x = prev_x * cos(camera->beta) + prev_z * sin(camera->beta);
	*z = -prev_x * sin(camera->beta) + prev_z * cos(camera->beta);
	prev_x = *x;
	prev_z = *z;
	// Rotation autour de l'axe Z
	*x = prev_x * cos(camera->gamma) - prev_y * sin(camera->gamma);
	*y = prev_x * sin(camera->gamma) + prev_y * cos(camera->gamma);
}

void	project_point(t_point *p, t_fdf *fdf)
{
	int	x;
	int	y;
	int	z;

	x = p->x;
	y = p->y;
	z = p->z;
	// Appliquer le zoom
	x *= fdf->camera->zoom;
	y *= fdf->camera->zoom;
	z *= fdf->camera->zoom;
	// Appliquer les rotations
	rotate_point(&x, &y, &z, fdf->camera);
	// Projection isométrique
	p->x = (x - y) * cos(0.523599) + fdf->camera->x_offset;
	p->y = -z + (x + y) * sin(0.523599) + fdf->camera->y_offset;
}

void	draw_line(t_img *img, t_point start, t_point end)
{
	double	delta_x;
	double	delta_y;
	double	pixel_x;
	double	pixel_y;
	int		pixels;

	delta_x = end.x - start.x;
	delta_y = end.y - start.y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = start.x;
	pixel_y = start.y;
	while (pixels)
	{
		put_pixel(img, pixel_x, pixel_y, start.color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}

