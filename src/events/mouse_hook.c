/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:52:27 by hadia             #+#    #+#             */
/*   Updated: 2025/03/28 16:58:06 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1) // Left mouse button
	{
		fdf->camera->x_offset += x;
		fdf->camera->y_offset += y;
	}
	else if (button == 4) // Scroll up
	{
		fdf->camera->scale += 0.1;
	}
	else if (button == 5) // Scroll down
	{
		fdf->camera->scale -= 0.1;
	}
	
	render(fdf);
	
	return (0);
}