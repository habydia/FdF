#include "fdf.h"

// //close the window when the red cross is clicked

int close(t_vars vars)
{
	mlx_destroy_window(vars.mlx, vars.win);
	exit(0);
	return (0);
}
int close_handler(int keycode, t_vars vars)
{
	(void)vars;
	if (keycode == K_ESC)
		exit(0);
	return (0);
}

void destroy(t_vars vars)
{
		mlx_hook(vars.win, KeyPress, KeyPressMask, close_handler, &vars); 
		mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close, &vars);
}
//int (*f)(void *param)