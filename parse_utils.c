#include "fdf.h"

int	get_width(char *line)
{
	int	width;
	int	i;

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

int	get_height(char *filename)
{
	int		height;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	height = 0;
	while (1)
	{
		if (!ft_get_next_line(fd, &line))
			break ;
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

static int	hex_to_int(const char *hex)
{
	int	result;

	if (!hex)
		return (DEFAULT_COLOR);
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		hex += 2;
	result = 0;
	while (*hex)
	{
		result *= 16;
		if (*hex >= '0' && *hex <= '9')
			result += *hex - '0';
		else if (*hex >= 'A' && *hex <= 'F')
			result += *hex - 'A' + 10;
		else if (*hex >= 'a' && *hex <= 'f')
			result += *hex - 'a' + 10;
		else
			break ;
		hex++;
	}
	return (result);
}

void	fill_point(t_point *point, int x, int y, char *str)
{
	char	**split;

	point->x = x;
	point->y = y;
	split = ft_split(str, ',');
	point->z = ft_atoi(split[0]);
	if (split[1])
		point->color = hex_to_int(split[1]);
	else
		point->color = DEFAULT_COLOR;
	ft_free_split(split);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
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
