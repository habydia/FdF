#include "fdf.h"

t_mlx *init_mlx(void)
{
    t_mlx *mlx;
    
    mlx = (t_mlx *)malloc(sizeof(t_mlx));
    if (!mlx)
        error("Memory allocation failed");
    
    mlx->mlx_ptr = mlx_init();
    if (!mlx->mlx_ptr)
        error("MLX initialization failed");
    
    mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "FDF");
    if (!mlx->win_ptr)
        error("Window creation failed");
    
    mlx->img_ptr = NULL;  // Important: initialize to NULL
    
    return (mlx);
}

void put_pixel(t_mlx *mlx, int x, int y, int color)
{
    char *dst;
    
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}