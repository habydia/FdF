#include "../include/fdf.h"
#include <math.h>

static void draw_line_low(t_mlx *mlx, t_point p1, t_point p2)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int yi = 1;
    
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }
    
    int d = (2 * dy) - dx;
    int y = p1.y;
    
    for (int x = p1.x; x <= p2.x; x++)
    {
        put_pixel(mlx, x, y, p1.color);
        if (d > 0)
        {
            y += yi;
            d += 2 * (dy - dx);
        }
        else
            d += 2 * dy;
    }
}

static void draw_line_high(t_mlx *mlx, t_point p1, t_point p2)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int xi = 1;
    
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }
    
    int d = (2 * dx) - dy;
    int x = p1.x;
    
    for (int y = p1.y; y <= p2.y; y++)
    {
        put_pixel(mlx, x, y, p1.color);
        if (d > 0)
        {
            x += xi;
            d += 2 * (dx - dy);
        }
        else
            d += 2 * dx;
    }
}

void draw_line(t_mlx *mlx, t_point p1, t_point p2)
{
    if (abs(p2.y - p1.y) < abs(p2.x - p1.x))
    {
        if (p1.x > p2.x)
            draw_line_low(mlx, p2, p1);
        else
            draw_line_low(mlx, p1, p2);
    }
    else
    {
        if (p1.y > p2.y)
            draw_line_high(mlx, p2, p1);
        else
            draw_line_high(mlx, p1, p2);
    }
}