#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int  ft_strlen(char *str)
{
    int count;

    count = 0;
    while (str && str[count])
        count++;
    return (count);
}

char	*ft_strdup(char *str)
{
	char	*s;
	int		i;

	i = 0;
	s = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!s)
		return (0);
	while (str && *str)
	{
		s[i] = *str;
		str++;
        i++;
	}
	s[i] = '\0';
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
        (str)++;
    if (*str == '\n')
       str++;
    new = ft_strdup(str);
    return (new);
}

size_t find_number(char *str)
{
    size_t  x;

    x = 0;
    if (*str == '\n')
        return 0;
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
    char    *temp;

    new = 1;
    total = 0;
    while (new != 0)
    {
        new = find_number(*str);
        total += new;
        temp = cut_input(*str);
        free(*str);
        *str = temp;
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
        buffer[read_bytes] = '\0';
        if (read_bytes)
            file_input = ft_strjoin(file_input, buffer);
    }
    return (file_input);
}

int main(void)
{
    int fd;
    size_t  max1;
    size_t  max2;
    size_t  max3;
    size_t  new;
    size_t  prev;
    char    *file;
    
    fd = open("input", O_RDONLY);
    file = read_file(fd);
    
    max1 = 0;
    max2 = 0;
    max3 = 0;
    while (file && *file)
    {
        new = add_chunks(&file);
        if (new > max1)
        {
            max3 = max2;
            max2 = max1;
            max1 = new;
        }
        else if (new > max2)
        {
            max3 = max2;
            max2 = new;
        }
        else if (new > max3)
            max3 = new;
       // printf("%zd\n", max);
    }

   printf("max1: %zd, max2: %zd, max3: %zd", max1, max2, max3);
   printf("MAXmax: %zd", max1 + max2 + max3);
    return (0);
}
