#include "../include/fdf.h"

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
    
    // Apply all three rotations
    rotate_x(&y, &z, fdf->camera->alpha);
    rotate_y(&x, &z, fdf->camera->beta);
    rotate_z(&x, &y, fdf->camera->gamma);
    
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