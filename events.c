#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	clean_exit(fdf);
	return (0);
}

static void	handle_rotation(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_Q)
		fdf->camera->alpha += 0.1;
	else if (keycode == KEY_A)
		fdf->camera->alpha -= 0.1;
	else if (keycode == KEY_W)
		fdf->camera->beta += 0.1;
	else if (keycode == KEY_S)
		fdf->camera->beta -= 0.1;
	else if (keycode == KEY_E)
		fdf->camera->gamma += 0.1;
	else if (keycode == KEY_D)
		fdf->camera->gamma -= 0.1;
}

static void	handle_translation(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_LEFT)
		fdf->camera->x_offset -= 10;
	else if (keycode == KEY_RIGHT)
		fdf->camera->x_offset += 10;
	else if (keycode == KEY_UP)
		fdf->camera->y_offset -= 10;
	else if (keycode == KEY_DOWN)
		fdf->camera->y_offset += 10;
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		close_window(fdf);
	handle_rotation(keycode, fdf);
	handle_translation(keycode, fdf);
	draw(fdf);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == MOUSE_UP)
		fdf->camera->zoom *= 1.1;
	else if (button == MOUSE_DOWN)
		fdf->camera->zoom /= 1.1;
	if (button == MOUSE_DOWN|| button == MOUSE_UP)
		draw(fdf);
	return (0);
}
