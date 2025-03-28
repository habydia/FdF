#include "fdf.h"

static t_camera *init_camera(void)
{
    t_camera *camera;
    
    camera = (t_camera *)malloc(sizeof(t_camera));
    if (!camera)
        error("Memory allocation failed");
    
    camera->alpha = 0;
    camera->beta = 0;
    camera->gamma = 0;
    camera->scale = 20;
    camera->x_offset = WIDTH / 2;
    camera->y_offset = HEIGHT / 2;
    camera->projection = 0;  // Isometric by default
    
    return (camera);
}

static void render_map(t_fdf *fdf)
{
    int x;
    int y;
    t_point p1;
    t_point p2;
    
    y = 0;
    while (y < fdf->map->height)
    {
        x = 0;
        while (x < fdf->map->width)
        {
            // Draw horizontal line
            if (x < fdf->map->width - 1)
            {
                p1 = (t_point){x, y, fdf->map->z_matrix[y][x], fdf->map->color_matrix[y][x]};
                p2 = (t_point){x + 1, y, fdf->map->z_matrix[y][x + 1], fdf->map->color_matrix[y][x + 1]};
                p1 = project(p1, fdf);
                p2 = project(p2, fdf);
                draw_line(fdf->mlx, p1, p2);
            }
            
            // Draw vertical line
            if (y < fdf->map->height - 1)
            {
                p1 = (t_point){x, y, fdf->map->z_matrix[y][x], fdf->map->color_matrix[y][x]};
                p2 = (t_point){x, y + 1, fdf->map->z_matrix[y + 1][x], fdf->map->color_matrix[y + 1][x]};
                p1 = project(p1, fdf);
                p2 = project(p2, fdf);
                draw_line(fdf->mlx, p1, p2);
            }
            
            x++;
        }
        y++;
    }
}

void render(t_fdf *fdf)
{
    // Clear image
    mlx_clear_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
    mlx_destroy_image(fdf->mlx->mlx_ptr, fdf->mlx->img_ptr);
    fdf->mlx->img_ptr = mlx_new_image(fdf->mlx->mlx_ptr, WIDTH, HEIGHT);
    fdf->mlx->addr = mlx_get_data_addr(fdf->mlx->img_ptr, &fdf->mlx->bits_per_pixel, 
                                      &fdf->mlx->line_length, &fdf->mlx->endian);
    
    // Render map
    render_map(fdf);
    
    // Put image to window
    mlx_put_image_to_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr, fdf->mlx->img_ptr, 0, 0);
}

int main(int argc, char **argv)
{
    (void)argc;
    t_fdf *fdf;
    
    // if (argc != 2)
    // {
    //     ft_putendl_fd("Usage: ./fdf <filename>", 2);
    //     return (1);
    // }
    
    fdf = (t_fdf *)malloc(sizeof(t_fdf));
    if (!fdf)
        error("Memory allocation failed");
    
    fdf->map = parse_map(argv[1]);
    fdf->camera = init_camera();
    fdf->mlx = init_mlx();
    
    render(fdf);
    
    mlx_key_hook(fdf->mlx->win_ptr, key_hook, fdf);
    mlx_mouse_hook(fdf->mlx->win_ptr, mouse_hook, fdf);
    mlx_loop(fdf->mlx->mlx_ptr);
    
    return (0);
}