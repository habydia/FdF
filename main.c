#include "fdf.h"

static void	init_camera(t_camera *camera)
{
	camera->zoom = 30;
	camera->alpha = 0;
	camera->beta = 0;
	camera->gamma = 0;
	camera->x_offset = WIN_WIDTH / 2;
	camera->y_offset = WIN_HEIGHT / 2;
}

void	init_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		clean_exit(fdf);
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!fdf->win)
		clean_exit(fdf);
	fdf->img = malloc(sizeof(t_img));
	if (!fdf->img)
		clean_exit(fdf);
	fdf->img->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img->img)
		clean_exit(fdf);
	fdf->img->addr = mlx_get_data_addr(fdf->img->img, &fdf->img->bits_per_pixel,
			&fdf->img->line_length, &fdf->img->endian);
	fdf->camera = malloc(sizeof(t_camera));
	if (!fdf->camera)
		clean_exit(fdf);
	init_camera(fdf->camera);
	fit_map_to_screen(fdf->camera, fdf->map, fdf);
}

void	clean_exit(t_fdf *fdf)
{
	if (fdf->map)
		free_map(fdf->map);
	if (fdf->camera)
		free(fdf->camera);
	if (fdf->img)
	{
		if (fdf->img->img)
			mlx_destroy_image(fdf->mlx, fdf->img->img);
		free(fdf->img);
	}
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	free(fdf);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_fdf *fdf;

	if (argc != 2)
	{
		write(2, "Usage: ./fdf map_file\n", 21);
		return (1);
	}
	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (1);
	fdf->map = NULL;
	fdf->camera = NULL;
	fdf->img = NULL;
	fdf->mlx = NULL;
	fdf->win = NULL;
	fdf->map = read_map(argv[1]);
	if (!fdf->map)
		clean_exit(fdf);
	init_fdf(fdf);
	mlx_hook(fdf->win, 2, 1L << 0, key_hook, fdf);
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
	mlx_mouse_hook(fdf->win, mouse_hook, fdf);
	draw(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
