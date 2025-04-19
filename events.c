#include "fdf.h"

int close_window(t_fdf *fdf)
{
    clean_exit(fdf);
    return (0);
}

static void handle_rotation(int keycode, t_fdf *fdf)
{
    if (keycode == 113) // Q - rotation X+
        fdf->camera->alpha += 0.1;
    else if (keycode == 97) // A - rotation X-
        fdf->camera->alpha -= 0.1;
    else if (keycode == 119) // W - rotation Y+
        fdf->camera->beta += 0.1;
    else if (keycode == 115) // S - rotation Y-
        fdf->camera->beta -= 0.1;
    else if (keycode == 101) // E - rotation Z+
        fdf->camera->gamma += 0.1;
    else if (keycode == 100) // D - rotation Z-
        fdf->camera->gamma -= 0.1;
}

static void handle_translation(int keycode, t_fdf *fdf)
{
    if (keycode == 65361) // Flèche gauche
        fdf->camera->x_offset -= 10;
    else if (keycode == 65363) // Flèche droite
        fdf->camera->x_offset += 10;
    else if (keycode == 65362) // Flèche haut
        fdf->camera->y_offset -= 10;
    else if (keycode == 65364) // Flèche bas
        fdf->camera->y_offset += 10;
}

int key_hook(int keycode, t_fdf *fdf)
{
    if (keycode == 65307) // ESC
        close_window(fdf);
    handle_rotation(keycode, fdf);
    handle_translation(keycode, fdf);
    draw(fdf);
    return (0);
}

int mouse_hook(int button, int x, int y, t_fdf *fdf)
{
    (void)x;
    (void)y;
    
    if (button == 4) // Molette vers le haut
        fdf->camera->zoom *= 1.1;
    else if (button == 5) // Molette vers le bas
        fdf->camera->zoom /= 1.1;
    
    if (button == 4 || button == 5)
        draw(fdf);
    return (0);
}