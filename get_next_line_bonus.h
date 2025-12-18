#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000 
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_List
{
	int				fd;
	char			*rest;
	struct s_List	*next;
}	t_List;

t_List	*get_node(t_List *head, int fd);
t_List	*ft_lstnew(int fd);
int		free_node(t_List **head, t_List *node);

char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
size_t	ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
char	*ft_strndup(char *str, size_t n);
char	*read_buffer(char *content, int fd);
char	*update_rest(char **rest);
char	*extract_line(char **line);

#endif
