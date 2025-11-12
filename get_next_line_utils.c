#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str++)
		i++;
	return (i);
}

char	*ft_strcpy(char *dst, char *src)
{
	char	*temp;

	if (!src)
		return (dst);
	temp = dst;
	while (*src)
		*temp++ = *src++;
	*temp = '\0';
	return (dst);
}

void	ft_strncat(char *dst, char *src, int c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (j < c)
		dst[i++] = src[j++];
	dst[i] = '\0';
}

char	*ft_strndup(char *str, size_t n)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = (char *)malloc(sizeof(char) * n + 1);
	if (!dup)
		return (NULL);
	while (i < n)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	free_str(char **str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (i < c)
		free(str[i++]);
	free(str);
}
