#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int  ft_strlen(char *str)
{
    int count;

    count = 0;
    while (str && str[count] != 0)
        count++;
    return (count);
}

char	*ft_strdup(char *s1)
{
	char	*s;
	int		i;

	i = 0;
	s = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s)
		return (0);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = 0;
    free(s1);
	return (s);
}

int replace_greatest(int x, int y)
{
    if (x > y)
        return (x);
    return (y);
}

char *cut_input(char *str)
{
    char    *new;
    

    while (str && *str != '\n' && *str != '\0')
        (*str)++;
    if (**str == '\n')
       (*str)++;
    new = ft_strdup(*str);
    free(*str);
    return (new);
}

int find_number(char *str)
{
    size_t  x;

    x = 0;
    while (str && *str != '\n' && *str != '\0')
    {
        x = x * 10 + (*str - '0');
        str++;
    }
    return (x);
}

size_t  add_chunks(char **str)
{
    size_t  total;
    size_t  new;

    new = 1;
    total = 0;
    while (new != 0)
    {
        new = find_number(*str);
        printf("new: %zd", new);
        total = total + new;
        printf("total %zd", total);
        *str = cut_input(str);
    }
    return (total);
}

char    *ft_strjoin(char *x, char *y)
{
    size_t  i;
    size_t  j;
    char    *joined;
    int     len;

    i = 0;
    j = 0;
    len = ft_strlen(x) + ft_strlen(y);
    joined = malloc(sizeof(char) * (len + 1));
    while (x && x[i])
    {
        joined[i] = x[i];
        i++;
    }
    while(y && y[j])
        joined[i++] = y[j++];
    joined[i] = 0;
    free(x);
    return (joined);
}

char    *read_file(int fd)
{
    ssize_t read_bytes;
    char    buffer[101];
    char    *file_input;

    read_bytes = 1;
    file_input = NULL;
    buffer[100] = 0;
        while (read_bytes != 0)
    {
        read_bytes = read(fd, buffer, 100);
        buffer[read_bytes] = 0;
        if (read_bytes)
            file_input = ft_strjoin(file_input, buffer);
    }
    return (file_input);
}

int main(void)
{
    int fd;
    size_t  max;
    size_t  new;
    size_t  prev;
    char    *file;
    
    fd = open("input", O_RDONLY);
    file = read_file(fd);
    
    max = 0;
   // printf("file_input %s\n", file);

    while (file && *file)
    {
        new = add_chunks(&file);
        max = replace_greatest(new, prev);
    }
    // printf("%zd\n", max);
    return (0);
}