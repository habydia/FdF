#include "fdf.h"

int get_width(char *line)
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

int get_height(char *filename)
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

int parse_line(char *line, t_point *points, int y)
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

