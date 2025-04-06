/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:02:43 by hadia             #+#    #+#             */
/*   Updated: 2025/04/06 16:19:36 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point project(t_point p, t_fdf *fdf)
{
    t_point projected;
    
    // First apply isometric projection
    projected.x = p.x - p.y;
    projected.y = (p.x + p.y) / 2 - p.z;
    projected.z = p.z;
    projected.color = p.color;
    
    // Then apply scale and offset
    projected.x = projected.x * fdf->camera->scale + fdf->camera->x_offset;
    projected.y = projected.y * fdf->camera->scale + fdf->camera->y_offset;
    
    return (projected);
}