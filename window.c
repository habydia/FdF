#include "fdf.h"

// //close the window when the red cross is clicked

int close_handler(int keycode, t_vars vars)
{
	(void)vars;
	if (keycode == K_ESC)
		exit(0);
	return (0);
}
//int (*f)(void *param)