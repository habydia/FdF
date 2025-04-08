/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:35:50 by hadia             #+#    #+#             */
/*   Updated: 2025/04/06 16:48:47 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


void free_map(t_map *map)
{
    int i;

    if (!map)
        return;
    if (map->z_matrix)
    {
        i = 0;
        while (i < map->height)
        {
            free(map->z_matrix[i]);
            i++;
        }
        free(map->z_matrix);
    }
    // Free color_matrix
    if (map->color_matrix)
    {
        i = 0;
        while (i < map->height)
        {
            free(map->color_matrix[i]);
            i++;
        }
        free(map->color_matrix);
    }
    free(map);
}

int close_window(t_fdf *fdf)
{
    // Free your structures
    free_map(fdf->map);
    free(fdf->camera);
    
    // Destroy MLX resources
    mlx_destroy_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
    mlx_destroy_display(fdf->mlx->mlx_ptr);
    free(fdf->mlx->mlx_ptr);
    free(fdf->mlx);
    
    // Exit program
    exit(0);
    return (0);
}