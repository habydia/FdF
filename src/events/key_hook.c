/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:23:51 by hadia             #+#    #+#             */
/*   Updated: 2025/04/12 16:13:36 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		close_window(fdf);
	else if (keycode == KEY_A)
		fdf->camera->alpha-= 0.1;
	else if (keycode == KEY_D)
		fdf->camera->alpha += 0.1;
	else if (keycode == KEY_W)
		fdf->camera->projection = 1;
	else if (keycode == KEY_F)
		fdf->camera->projection = 2;
	else if(keycode == KEY_S)
		fdf->camera->projection = 0;
	
	render(fdf);

	return (0);
}
