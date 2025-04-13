/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:35:50 by hadia             #+#    #+#             */
/*   Updated: 2025/04/12 16:45:41 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


void free_map(t_map *map)
{
    int i;

    if (!map)
        return;
    // Free z_matrix
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
    // First destroy the image
    if (fdf && fdf->mlx && fdf->mlx->img_ptr)
    {
        mlx_destroy_image(fdf->mlx->mlx_ptr, fdf->mlx->img_ptr);
        fdf->mlx->img_ptr = NULL;
    }
    
    // Then destroy the window
    if (fdf && fdf->mlx && fdf->mlx->win_ptr)
    {
        mlx_destroy_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
        fdf->mlx->win_ptr = NULL;
    }
    
    // Free map data structures
    if (fdf && fdf->map)
    {
        free_map(fdf->map);
        fdf->map = NULL;
    }
    
    // Free camera
    if (fdf && fdf->camera)
    {
        free(fdf->camera);
        fdf->camera = NULL;
    }
    
    // Free the MLX display (important: must be after destroying windows and images)
    if (fdf && fdf->mlx && fdf->mlx->mlx_ptr)
    {
        mlx_destroy_display(fdf->mlx->mlx_ptr);
        free(fdf->mlx->mlx_ptr);
        fdf->mlx->mlx_ptr = NULL;
    }
    
    // Finally free the MLX struct itself
    if (fdf && fdf->mlx)
    {
        free(fdf->mlx);
        fdf->mlx = NULL;
    }
    
    // Free the main struct
    if (fdf)
    {
        free(fdf);
    }
    
    exit(0);
    return (0);
}
