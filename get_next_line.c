#include "get_next_line.h"

int	is_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_free_join(char **strs, char *buffer, int n, int c)
{
	size_t	len;
	int		i;
	char	*join;

	i = 0;
	len = 0;
	if (!strs)
		return (NULL);
	strs[c] = NULL;
	while (i < c)
		len += ft_strlen(strs[i++]);
	join = malloc(sizeof(char) * (len + 1) + BUFFER_SIZE + 1);
	if (!join)
		return (NULL);
	join[0] = '\0';
	i = -1;
	while (++i < c)
		ft_strncat(join, strs[i], ft_strlen(strs[i]));
	ft_strncat(join, buffer, n);
	free_str(strs, c);
	return (join);
}

char	*first_nl(int fd, char *rest)
{
	char		**prev_buffer;
	char		buffer[BUFFER_SIZE];
	int			i;
	int			pos;
	ssize_t		nbytes;

	prev_buffer = malloc(sizeof(char *) * 4 * BUFFER_SIZE + 1);
	if (!prev_buffer)
		return (NULL);
	i = 0;
	if (rest && *rest)
		prev_buffer[i++] = ft_strndup(rest, ft_strlen(rest) + 1);
	nbytes = read(fd, buffer, BUFFER_SIZE - 1);
	while (nbytes)
	{
		buffer[nbytes] = '\0';
		pos = is_newline(buffer);
		if (pos >= 0)
		{
			ft_strcpy(rest, buffer, pos + 1);
			return (ft_free_join(prev_buffer, buffer, pos + 1, i));
		}
		prev_buffer[i++] = ft_strndup(buffer, BUFFER_SIZE - 1);
		nbytes = read(fd, buffer, BUFFER_SIZE - 1);
	}
	free(prev_buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	int			pos;

	if (rest && *rest)
	{
		pos = is_newline(rest);
		if (pos >= 0)
		{
			line = ft_strndup(rest, (size_t) pos + 1);
			ft_strcpy(rest, rest, pos + 1);
			return (line);
		}
	}
	else
	{
		rest = malloc(sizeof(char) * 54 * BUFFER_SIZE + 1);
		if (!rest)
			return (NULL);
		rest[0] = '\0';
	}
	line = first_nl(fd, rest);
	if (line == NULL)
	{
		free(rest);
		return (NULL);
	}
	return (line);
}

void	read_file(char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd != -1)
	{
		while ((line = get_next_line(fd)))
		{
			printf("line : %s", line);
			free(line);
		}
	}
	else
		printf("bug");
}

int main(int argc, char **arg)
{
	char *line; 
    (void)argc;

	if(arg[1])
		read_file(arg[1]);
	else 
	{
		while ((line = get_next_line(0)))
		{	
			printf("line = %s", line);
			free(line);
		}
	}
}
