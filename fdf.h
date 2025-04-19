#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "mlx_linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define DEFAULT_COLOR 0xFFFFFF

# define KEY_ESC 65307
# define KEY_Q 113
# define KEY_A 97
# define KEY_W 119
# define KEY_S 115
# define KEY_E 101
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define MOUSE_UP 4
# define MOUSE_DOWN 5

typedef struct s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_point;

typedef struct s_map
{
	t_point		**points;
	int			width;
	int			height;
	int			z_min;
	int			z_max;
}				t_map;

typedef struct s_bounds
{
	double		x_min;
	double		x_max;
	double		y_min;
	double		y_max;
}				t_bounds;

typedef struct s_camera
{
	double		zoom;
	double		alpha;
	double		beta;
	double		gamma;
	int			x_offset;
	int			y_offset;
}				t_camera;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_camera	*camera;
	t_img		*img;
}				t_fdf;

// Fonctions de parsing
int				parse_line(char *line, t_point *points, int y);
int				get_height(char *filename);
int				get_width(char *line);
t_map			*read_map(char *filename);

// Fonctions de dessin
void			draw_line(t_img *img, t_point start, t_point end);
void			draw(t_fdf *fdf);
void			project_point(t_point *p, t_fdf *fdf);

// Fonctions d'événements
int				key_hook(int keycode, t_fdf *fdf);
int				mouse_hook(int button, int x, int y, t_fdf *fdf);
int				close_window(t_fdf *fdf);

// Fonctions utilitaires
char			*ft_get_next_line(int fd, char **line);
void			fit_map_to_screen(t_camera *camera, t_map *map, t_fdf *fdf);
void			init_fdf(t_fdf *fdf);
void			free_map(t_map *map);
void			clean_exit(t_fdf *fdf);
void			put_pixel(t_img *img, int x, int y, int color);

#endif