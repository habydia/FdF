#include "fdf.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static int ft_wordcount(char *str, char delimiter)
{
    int count = 0;
    int i = 0;

    while (str[i])
    {
        while (str[i] && str[i] == delimiter)
            i++;
        if (str[i])
            count++;
        while (str[i] && str[i] != delimiter)
            i++;
    }
    return (count);
}

void read_map_size(char *filename, int *width, int *height)
{
    int fd;
    char *line;
    
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error("Failed to open the file");
    
    *height = 0;
    *width = 0;
    
    while (ft_get_next_line(fd, &line)  && ft_strlen(line)> 0)
    {
        if (*height == 0)
            *width = ft_wordcount(line, ' ');
        (*height)++;
        free(line);
    }
    close(fd);
    if (*width == 0 || *height == 0)
        error("Invalid map");
}

static void fill_matrix(int **z_matrix, int **color_matrix, char *line, int y)
{
    char **split;
    int x;
    char *color_ptr;
    
    split = ft_split(line, ' ');
    x = 0;
    while (split[x])
    {
        z_matrix[y][x] = ft_atoi(split[x]);
        color_ptr = ft_strchr(split[x], ',');
        if (color_ptr)
            color_matrix[y][x] = ft_atoi_base(color_ptr + 1, 16);
        else
            color_matrix[y][x] = WHITE;  // Default color
        x++;
        free(split[x]);
    }
    free(split);
}

t_map *parse_map(char *filename)
{
    t_map *map;
    int fd;
    char *line;
    int y;
    
    map = (t_map *)malloc(sizeof(t_map));
    if (!map)
        error("Memory allocation failed");
    
    read_map_size(filename, &map->width, &map->height);
    
    // Allocate memory for z and color matrices
    map->z_matrix = (int **)malloc(sizeof(int *) * map->height);
    map->color_matrix = (int **)malloc(sizeof(int *) * map->height);
    for (int i = 0; i < map->height; i++)
    {
        map->z_matrix[i] = (int *)malloc(sizeof(int) * map->width);
        map->color_matrix[i] = (int *)malloc(sizeof(int) * map->width);
    }
    
    // Fill matrices
    fd = open(filename, O_RDONLY);
    y = 0;
    while (ft_get_next_line(fd, &line) && ft_strlen(line)> 0)
    {
        fill_matrix(map->z_matrix, map->color_matrix, line, y++);
        free(line);
    }
    close(fd);
    
    return (map);
}