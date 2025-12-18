#include "get_next_line.h"

static t_List	*get_node(t_List *List, int fd)
{
	if (List == NULL)
		return (NULL);
	while (List && List->next)
	{
		if (List->fd == fd)
			return (List);
		List = List->next;
	}
	if (List->fd == fd)
		return (List);
	List->next = ft_lstnew(fd);
	return (List->next);
}

static int	free_node(t_List **head, t_List *node)
{
	t_List	*temp;

	temp = *head;
	if (*head == node)
	{
		*head = node->next;
		return (free(node->rest), node->rest = NULL, free(node), 1);
	}
	while (temp->next)
	{
		if (temp->next == node)
		{
			temp->next = node->next;
			return (free(node->rest), node->rest = NULL, free(node), 1);
		}
		temp = temp->next;
	}
	return (0);
}

static char	*read_buffer(char *content, int fd)
{
	int		nbytes_read;
	char	*buffer;

	if (content && ft_strchr(content, '\n'))
		return (content);
	buffer = malloc(sizeof(*buffer) * BUFFER_SIZE + 1);
	if (!buffer)
		return (free(content), NULL);
	nbytes_read = 5;
	while (nbytes_read > 0)
	{
		nbytes_read = read(fd, buffer, BUFFER_SIZE);
		if (nbytes_read == -1)
			return (free(buffer), buffer = NULL, free(content), NULL);
		buffer[nbytes_read] = '\0';
		if (nbytes_read != 0)
			content = ft_strjoin(content, buffer);
		if (!content || !content[0] || ft_strchr(content, '\n'))
			break ;
	}
	return (free(buffer), buffer = NULL, content);
}

static char	*extract_line(char **dirty_line)
{
	char	*clean_line;
	char	*temp;
	int		i;

	i = 0;
	if (!(*dirty_line)[0] || !*dirty_line || !dirty_line)
		return (NULL);
	while ((*dirty_line)[i] != '\n' && (*dirty_line)[i])
		i++;
	if ((*dirty_line)[i] == '\n')
		i++;
	clean_line = ft_strndup(*dirty_line, i);
	temp = ft_strndup(&(*dirty_line)[i], ft_strlen(*dirty_line) - i);
	if (!temp)
		return (free(clean_line), clean_line = NULL, NULL);
	free(*dirty_line);
	*dirty_line = temp;
	return (clean_line);
}

char	*get_next_line(int fd)
{
	static t_List	*head;
	t_List			*node;
	char			*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!head)
		head = ft_lstnew(fd);
	node = get_node(head, fd);
	if (!node)
		return (NULL);
	node->rest = read_buffer(node->rest, fd);
	if (!node->rest || !node->rest[0])
		return (free_node(&head, node), NULL);
	line = extract_line(&node->rest);
	if (!line || !node->rest)
		return (free(node->rest), node->rest = NULL, NULL);
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
