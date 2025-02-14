#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
#include "mlx_linux/mlx.h"

# define K_ESC 65307
//structure pour les données de l'image
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}							t_data;

//gestion fenetre
typedef struct s_vars
{
	void	*mlx;
	void	*win;
}							t_vars;

//fonctions fermerture fenetre
int close_handler(int keycode, t_vars vars);

//fonctions pour les images
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif