#include "fdf.h"

char	*add_stock_buffer(char *buffer, ssize_t bytes_read, char *stock_buf)
{
	char	*tmp;

	if (buffer)
	{
		tmp = buffer;
		buffer = malloc(ft_strlen(tmp) + bytes_read + 1);
		if (!buffer)
		{
			free(tmp);
			return (NULL);
		}
		ft_strcpy(buffer, tmp);
		ft_strcat(buffer, stock_buf);
		free(tmp);
	}
	else
	{
		buffer = malloc(bytes_read + 1);
		if (!buffer)
			return (NULL);
		ft_strcpy(buffer, stock_buf);
	}
	return (buffer);
}

char	*read_fd(int fd, char *buffer)
{
	char	*stock_buf;
	ssize_t	bytes_read;

	stock_buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!stock_buf)
		return (free(buffer), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!buffer || !ft_strchr(buffer, '\n')))
	{
		bytes_read = read(fd, stock_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(stock_buf), free(buffer), NULL);
		stock_buf[bytes_read] = '\0';
		buffer = add_stock_buffer(buffer, bytes_read, stock_buf);
		if (!buffer)
			return (free(stock_buf), NULL);
	}
	free(stock_buf);
	if (bytes_read == -1 || (bytes_read == 0 && (!buffer || *buffer == '\0')))
		return (free(buffer), NULL);
	return (buffer);
}

char	*extract_line(char **buffer)
{
	char	*newline_pos;
	char	*line;
	size_t	len;

	newline_pos = ft_strchr(*buffer, '\n');
	if (newline_pos)
	{
		len = newline_pos - *buffer + 1;
		line = malloc(len + 1);
		if (!line)
			return (NULL);
		ft_strncpy(line, *buffer, len);
		line[len] = '\0';
		ft_memmove(*buffer, newline_pos + 1, ft_strlen(newline_pos + 1) + 1);
	}
	else
	{
		line = malloc(ft_strlen(*buffer) + 1);
		if (!line)
			return (NULL);
		ft_strcpy(line, *buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*ft_get_next_line(int fd, char **line)
{
	char		*t_line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		return (0);
	}
	buffer = read_fd(fd, buffer);
	if (!buffer)
		return (NULL);
	t_line = extract_line(&buffer);
	if (!t_line || (buffer && *buffer == '\0'))
	{
		free(buffer);
		buffer = NULL;
	}
	*line = t_line;
	return (*line);
}