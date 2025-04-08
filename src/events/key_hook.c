/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:23:51 by hadia             #+#    #+#             */
/*   Updated: 2025/04/06 19:32:50 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int key_hook(int keycode, t_fdf *fdf)
{
    if (keycode == KEY_ESC)
    {
        close_window(fdf);
    }
    // X-axis rotation (alpha)
    else if (keycode == KEY_Q)
    {
        fdf->camera->alpha += 0.1;
    }
    else if (keycode == KEY_W)
    {
        fdf->camera->alpha -= 0.1;
    }
    // Y-axis rotation (beta)
    else if (keycode == KEY_A)
    {
        fdf->camera->beta += 0.1;
    }
    else if (keycode == KEY_S)
    {
        fdf->camera->beta -= 0.1;
    }
    // Z-axis rotation (gamma)
    else if (keycode == KEY_Z)
    {
        fdf->camera->gamma += 0.1;
    }
    else if (keycode == KEY_X)
    {
        fdf->camera->gamma -= 0.1;
    }
    // Zoom controls
    else if (keycode == KEY_PLUS || keycode == KEY_E)
    {
        fdf->camera->scale *= 1.1;
    }
    else if (keycode == KEY_MINUS || keycode == KEY_D)
    {
        fdf->camera->scale *= 0.9;
    }
    // Movement controls
    else if (keycode == KEY_UP)
    {
        fdf->camera->y_offset -= 10;
    }
    else if (keycode == KEY_DOWN)
    {
        fdf->camera->y_offset += 10;
    }
    else if (keycode == KEY_LEFT)
    {
        fdf->camera->x_offset -= 10;
    }
    else if (keycode == KEY_RIGHT)
    {
        fdf->camera->x_offset += 10;
    }
    // Reset view
    else if (keycode == KEY_R)
    {
        fdf->camera->alpha = 0;
        fdf->camera->beta = 0;
        fdf->camera->gamma = 0;
        fdf->camera->scale = 20;
        fdf->camera->x_offset = WIDTH / 2;
        fdf->camera->y_offset = HEIGHT / 2;
    }
    
    render(fdf);
    
    return (0);
}