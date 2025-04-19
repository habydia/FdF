#include "fdf.h"

static int	init_map(t_map **map, int height)
{
	*map = malloc(sizeof(t_map));
	if (!*map)
		return (0);
	(*map)->height = height;
	(*map)->points = malloc(sizeof(t_point *) * height);
	if (!(*map)->points)
	{
		free(*map);
		return (0);
	}
	return (1);
}

static int	alloc_points(t_map *map, int width)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		map->points[i] = malloc(sizeof(t_point) * width);
		if (!map->points[i])
		{
			map->height = i;
			free_map(map);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	read_and_parse_lines(t_map *map, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (i < map->height)
	{
		if (!ft_get_next_line(fd, &line))
			return (0);
		if (i == 0)
		{
			map->width = get_width(line);
			free(map->points[0]);
			map->points[0] = malloc(sizeof(t_point) * map->width);
			if (!map->points[0])
				return (free(line), 0);
		}
		if (!parse_line(line, map->points[i], i))
			return (free(line), 0);
		free(line);
		i++;
	}
	return (1);
}

t_map	*read_map(char *filename)
{
	t_map	*map;
	int		fd;
	int		height;

	height = get_height(filename);
	if (height <= 0 || !init_map(&map, height))
		return (NULL);
	map->width = 0;
	if (!alloc_points(map, 1024))
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free_map(map), NULL);
	if (!read_and_parse_lines(map, fd))
		return (close(fd), free_map(map), NULL);
	close(fd);
	return (map);
}
