/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:23:51 by hadia             #+#    #+#             */
/*   Updated: 2025/03/28 16:56:46 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
		free(fdf->map);
		free(fdf->camera);
		free(fdf->mlx);
		exit(0);
	}
	// else if (keycode == KEY_W)
	// {
	// 	fdf->camera->zoom += 1;
	// }
	// else if (keycode == KEY_S)
	// {
	// 	fdf->camera->zoom -= 1;
	// }
	else if (keycode == KEY_A)
	{
		fdf->camera->alpha-= 0.1;
	}
	else if (keycode == KEY_D)
	{
		fdf->camera->alpha += 0.1;
	}
	
	render(fdf);
	
	return (0);
}