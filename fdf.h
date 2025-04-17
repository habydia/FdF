#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx_linux/mlx.h"
# include "libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define DEFAULT_COLOR 0xFFFFFF

typedef struct s_point
{
    int x;
    int y;
    int z;
    int color;
} t_point;

typedef struct s_map
{
    t_point **points;
    int width;
    int height;
    int z_min;
    int z_max;
} t_map;

typedef struct s_camera
{
    double zoom;
    double alpha;
    double beta;
    double gamma;
    int x_offset;
    int y_offset;
} t_camera;

typedef struct s_img
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_img;

typedef struct s_fdf
{
    void *mlx;
    void *win;
    t_map *map;
    t_camera *camera;
    t_img *img;
} t_fdf;

// Fonction get_next_line
char *ft_get_next_line(int fd, char **line);

// Fonctions de parsing
t_map *read_map(char *filename);

// Fonctions de dessin
void draw(t_fdf *fdf);

// Fonctions d'événements
int key_hook(int keycode, t_fdf *fdf);
int mouse_hook(int button, int x, int y, t_fdf *fdf);
int close_window(t_fdf *fdf);

// Fonctions utilitaires
void init_fdf(t_fdf *fdf);
void free_map(t_map *map);
void clean_exit(t_fdf *fdf);
void put_pixel(t_img *img, int x, int y, int color);

#endif 