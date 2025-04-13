#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# include <math.h>
# include <../libft/libft.h>
# include <../mlx_linux/mlx.h>
# include "../libft/libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

/* Colors */
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

/* Key codes */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101
# define KEY_R 114
# define KEY_F 102
# define KEY_PLUS 61
# define KEY_MINUS 45

/* Window dimensions */
# define WIDTH 1200
# define HEIGHT 800

typedef struct s_point {
    int x;
    int y;
    int z;
    int color;
} t_point;

typedef struct s_map {
    int width;
    int height;
    int **z_matrix;
    int **color_matrix;
    int z_min;
    int z_max;
} t_map;

typedef struct s_camera {
    double alpha;  // rotation x
    double beta;   // rotation y
    double gamma;  // rotation z
    double scale;
    int x_offset;
    int y_offset;
    int projection; // 0 for isometric, 1 for parallel
} t_camera;

typedef struct s_mlx {
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_mlx;

typedef struct s_fdf {
    t_map *map;
    t_camera *camera;
    t_mlx *mlx;
} t_fdf;

/* Parsing functions */
t_map *parse_map(char *filename);
void read_map_size(char *filename, int *width, int *height);

/* Graphics functions */
t_mlx *init_mlx(void);
void draw_line(t_mlx *mlx, t_point p1, t_point p2);
void put_pixel(t_mlx *mlx, int x, int y, int color);
void render(t_fdf *fdf);

/* Math functions */
t_point project(t_point p, t_fdf *fdf);

/* Events functions */
int key_hook(int keycode, t_fdf *fdf);
int mouse_hook(int button, int x, int y,t_fdf *fdf);

/* Utils functions */
void free_map(t_map *map);
int close_window(t_fdf *fdf);
char	*ft_get_next_line(int fd, char **line);
void error(char *message);
int ft_atoi_base(char *str, int base);
int get_color(int z, t_map *map);

#endif