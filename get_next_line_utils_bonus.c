#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	c = (char) c;
	len = ft_strlen(s);
	i = 0;
	while (i < len + 1)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strndup(char *s, size_t n)
{
	char	*cpy;
	size_t	i;

	if (!s)
		return (NULL);
	cpy = malloc(sizeof(*cpy) * n + 1);
	if (!cpy || !s)
		return (NULL);
	i = 0;
	while (i < n)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

t_List	*ft_lstnew(int fd)
{
	t_List	*elem;

	elem = malloc(sizeof(t_List));
	if (!elem)
		return (NULL);
	elem->rest = ft_strndup("", 0);
	if (!elem->rest)
		return (NULL);
	elem->next = NULL;
	elem->fd = fd;
	return (elem);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*conq;
	size_t	len;
	int		i;
	int		k;
	int		j;

	k = 0;
	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	conq = malloc(sizeof(char) * len + 1);
	if (!conq)
	{
		free(s1);
		s1 = NULL;
		return (NULL);
	}
	while (s1[k])
		conq[i++] = s1[k++];
	while (s2[j])
		conq[i++] = s2[j++];
	conq[i] = '\0';
	return (free(s1), s1 = NULL, conq);
}
