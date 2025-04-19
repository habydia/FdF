#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	clean_exit(fdf);
	return (0);
}

static void	handle_rotation(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_Q) // Q - rotation X+
		fdf->camera->alpha += 0.1;
	else if (keycode == KEY_A) // A - rotation X-
		fdf->camera->alpha -= 0.1;
	else if (keycode == KEY_W) // W - rotation Y+
		fdf->camera->beta += 0.1;
	else if (keycode == KEY_S) // S - rotation Y-
		fdf->camera->beta -= 0.1;
	else if (keycode == KEY_E) // E - rotation Z+
		fdf->camera->gamma += 0.1;
	else if (keycode == KEY_D) // D - rotation Z-
		fdf->camera->gamma -= 0.1;
}

static void	handle_translation(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_LEFT) // Flèche gauche
		fdf->camera->x_offset -= 10;
	else if (keycode == KEY_RIGHT) // Flèche droite
		fdf->camera->x_offset += 10;
	else if (keycode == KEY_UP) // Flèche haut
		fdf->camera->y_offset -= 10;
	else if (keycode == KEY_DOWN) // Flèche bas
		fdf->camera->y_offset += 10;
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC) // ESC
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

	if (MOUSE_UP|| MOUSE_DOWN)
		draw(fdf);
	return (0);
}
