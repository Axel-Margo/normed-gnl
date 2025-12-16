#include "get_next_line.h"

t_List	*get_node(t_List *node, int fd)
{
	if (!node)
		return (NULL);
	while (node->next)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	if (node->fd == fd)
		return (node);
	node->next = ft_lstnew(fd);
	return (node->next);
}

char	*read_buffer(char *content, int fd)
{
	int		nbytes_read;
	char	*buffer;

	if (content && ft_strchr(content, '\n'))
		return (content);
	buffer = malloc(sizeof(*buffer) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	nbytes_read = 5;
	while (nbytes_read > 0)
	{
		nbytes_read = read(fd, buffer, BUFFER_SIZE);
		if (nbytes_read == -1)
			return (free(buffer), free(content), NULL);
		buffer[nbytes_read] = '\0';
		if (nbytes_read != 0)
			content = ft_strjoin(content, buffer);
		if (!content || !content[0] || ft_strchr(content, '\n'))
			break ;
	}
	return (free(buffer), content);
}

char	*extract_line(char *dirty_line)
{
	char	*clean_line;
	int		i;

	i = 0;
	if (!dirty_line[0] || !dirty_line)
		return (NULL);
	while (dirty_line[i] != '\n' && dirty_line[i])
		i++;
	if (dirty_line[i] == '\n')
		i++;
	clean_line = ft_strndup(dirty_line, i);
	return (clean_line);
}

char	*update_rest(char **rest)
{
	size_t	i;
	char	*new_rest;

	if (!rest || !*rest || !(*rest)[0])
		return (NULL);
	i = 0;
	while ((*rest)[i] != '\n' && (*rest)[i])
		i++;
	if ((*rest)[i] == '\n')
		i++;
	new_rest = ft_strndup(&(*rest)[i], ft_strlen(*rest) - i);
	free(*rest);
	*rest = NULL;
	return (new_rest);
}

char	*get_next_line(int fd)
{
	static t_List	*head;
	t_List			*node;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!head)
		head = ft_lstnew(fd);
	node = get_node(head, fd);
	if (!node)
		return (NULL);
	node->rest = read_buffer(node->rest, fd);
	if (!node->rest || !node->rest[0])
		return (free(node->rest), node->rest = NULL, free(head), head = NULL, NULL);
	line = extract_line(node->rest);
	if (!line)
		return (NULL);
	node->rest = update_rest(&node->rest);
	if (!node->rest)
		return (node->rest = NULL, NULL);
	return (line);
}
/*
void	read_file(char *filename)
{
	char	*line;
	int		fd = open(filename, O_RDONLY);
	int		i = 0;

	if (fd != -1)
	{
		while (i < 14)
		{	
			line = get_next_line(fd);
			printf("line = %s", line);
			if (line)
				free(line);
			i++;
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
*/
