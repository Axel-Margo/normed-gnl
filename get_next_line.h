#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

size_t	ft_strlen(char *str);
char	*ft_strcpy(char *dst, char *src, int pos);
void	ft_strncat(char *dst, char *str, int c);
void	free_str(char **str, int c);
char	*ft_strndup(char *str, size_t n);
char	*ft_free_join(char **strs, char *buffer, int n, int c);

#endif
