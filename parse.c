#include "fdf.h"

static int get_width(char *line)
{
    int width;
    int i;

    width = 0;
    i = 0;
    while (line[i])
    {
        while (line[i] && line[i] == ' ')
            i++;
        if (line[i])
            width++;
        while (line[i] && line[i] != ' ')
            i++;
    }
    return (width);
}

static int get_height(char *filename)
{
    int height;
    int fd;
    char *line;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (-1);
    height = 0;
    while (1)
    {
        if (!ft_get_next_line(fd, &line))
            break;
        height++;
        free(line);
    }
    close(fd);
    return (height);
}

static void fill_point(t_point *point, int x, int y, char *str)
{
    point->x = x;
    point->y = y;
    point->z = ft_atoi(str);
    point->color = DEFAULT_COLOR;
}

static int parse_line(char *line, t_point *points, int y)
{
    char **split;
    int x;
    int i;

    split = ft_split(line, ' ');
    if (!split)
        return (0);
    x = 0;
    i = 0;
    while (split[i])
    {
        fill_point(&points[x], x, y, split[i]);
        free(split[i]);
        i++;
        x++;
    }
    free(split);
    return (1);
}

void free_map(t_map *map)
{
    int i;

    if (!map)
        return;
    if (map->points)
    {
        i = 0;
        while (i < map->height)
        {
            if (map->points[i])
                free(map->points[i]);
            i++;
        }
        free(map->points);
    }
    free(map);
}

t_map *read_map(char *filename)
{
    t_map *map;
    int fd;
    char *line;
    int i;

    map = malloc(sizeof(t_map));
    if (!map)
        return (NULL);
    map->height = get_height(filename);
    if (map->height <= 0)
    {
        free(map);
        return (NULL);
    }
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        free(map);
        return (NULL);
    }
    if (!ft_get_next_line(fd, &line))
    {
        free(map);
        close(fd);
        return (NULL);
    }
    map->width = get_width(line);
    free(line);
    if (map->width <= 0)
    {
        free(map);
        close(fd);
        return (NULL);
    }
    map->points = malloc(sizeof(t_point *) * map->height);
    if (!map->points)
    {
        free(map);
        close(fd);
        return (NULL);
    }
    i = 0;
    while (i < map->height)
    {
        map->points[i] = malloc(sizeof(t_point) * map->width);
        if (!map->points[i])
        {
            map->height = i;
            free_map(map);
            close(fd);
            return (NULL);
        }
        i++;
    }
    close(fd);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        free_map(map);
        return (NULL);
    }
    i = 0;
    while (i < map->height)
    {
        if (!ft_get_next_line(fd, &line) || !parse_line(line, map->points[i], i))
        {
            if (line)
                free(line);
            free_map(map);
            close(fd);
            return (NULL);
        }
        free(line);
        i++;
    }
    close(fd);
    return (map);
} 