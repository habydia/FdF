/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:02:43 by hadia             #+#    #+#             */
/*   Updated: 2025/04/12 16:08:57 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Applies rotation matrix around X axis
static void rotate_x(int *y, int *z, double alpha)
{
    int prev_y = *y;
    *y = prev_y * cos(alpha) + *z * sin(alpha);
    *z = -prev_y * sin(alpha) + *z * cos(alpha);
}

// Applies rotation matrix around Y axis
static void rotate_y(int *x, int *z, double beta)
{
    int prev_x = *x;
    *x = prev_x * cos(beta) + *z * sin(beta);
    *z = -prev_x * sin(beta) + *z * cos(beta);
}

// Applies rotation matrix around Z axis
static void rotate_z(int *x, int *y, double gamma)
{
    int prev_x = *x;
    *x = prev_x * cos(gamma) - *y * sin(gamma);
    *y = prev_x * sin(gamma) + *y * cos(gamma);
}

// Top-down view (X rotation 90 degrees)
// Top-down view (X rotation 90 degrees) with additional rotations
static void para_project(int *x, int *y, int *z, t_fdf *fdf)
{
    // Apply base parallel projection
    rotate_x(y, z, M_PI/2);
    
    // Then apply user camera rotations for fine-tuning
    rotate_x(y, z, fdf->camera->alpha);
    rotate_y(x, z, fdf->camera->beta);
    rotate_z(x, y, fdf->camera->gamma);
    
    // Flatten z for parallel projection
    *z = 0;
}

// Front view (Y rotation 90 degrees) with additional rotations
static void conic_project(int *x, int *y, int *z, t_fdf *fdf)
{
    // Apply base conic projection
    rotate_y(x, z, M_PI/2);
    
    // Then apply user camera rotations for fine-tuning
    rotate_x(y, z, fdf->camera->alpha);
    rotate_y(x, z, fdf->camera->beta);
    rotate_z(x, y, fdf->camera->gamma);
    
    *z = (*z - fdf->map->z_min);
}

// Isometric view (balanced rotations)
static void iso_project(int *x, int *y, int *z, t_fdf *fdf)
{
    rotate_x(y, z, fdf->camera->alpha);
    rotate_y(x, z, fdf->camera->beta);
    rotate_z(x, y, fdf->camera->gamma);
}

t_point project(t_point p, t_fdf *fdf)
{
    t_point projected;
    int x;
    int y;
    int z;
    
    // Copy the original point values
    x = p.x;
    y = p.y;
    z = p.z;

    // Apply projection based on selected mode
    if (fdf->camera->projection == 0)
        iso_project(&x, &y, &z, fdf);
    else if (fdf->camera->projection == 1)
        conic_project(&x, &y, &z, fdf);
    else if (fdf->camera->projection == 2)
        para_project(&x, &y, &z, fdf);
        
    // Store the rotated values
    projected.x = x;
    projected.y = y;
    projected.z = z;
    projected.color = p.color;
    
    // Apply scale and offset
    projected.x = projected.x * fdf->camera->scale + fdf->camera->x_offset;
    projected.y = projected.y * fdf->camera->scale + fdf->camera->y_offset;
    
    return (projected);
}