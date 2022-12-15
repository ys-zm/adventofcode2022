// A Y  A=Rock ; Y=Paper; 
// B X  B=Paper ; X=Paper;
// C Z  C=Scissors ; Z=Scissors;

//Scores
// 0-lost / 3-draw / 6-won
// 1-Rock / 2-Paper / 3-Scissors

//check status/ check my move/ add scores.

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
        if (read_bytes < 0)
            return (NULL);
        buffer[read_bytes] = '\0';
        if (read_bytes)
            file_input = ft_strjoin(file_input, buffer);
    }
    return (file_input);
}

size_t  ft_round(char *file)
{
    char    opponent_play;
    char    my_play;
    char    opp[3] = {'A', 'B', 'C'};
    char    my[3] = {'X', 'Y', 'Z'};
    size_t  opp_i;
    size_t  my_i;

    opp_i = 0;
    my_i = 0;
    opponent_play = file[0];
    my_play = file[2];
    while (opp[opp_i] != opponent_play && opp[opp_i] != 0)
        opp_i++;
    while (my[my_i] != my_play && my[my_i] != 0)
        my_i++;
    if (opp_i == my_i)
        return (2); //we draw = 2
    else if (opp_i == 0)
    {
        if (my_i == 1)
            return (1); //i win = 1
        else if (my_i == 2)
            return (0); //i lose = 0
    }
    else if (opp_i == 1)
    {
        if (my_i == 0)
            return (0);
        else if (my_i == 2)
            return (1);
    }
    else if (opp_i == 2)
    {
        if (my_i == 0)
            return (1);
        else if (my_i == 1)
            return (0);
    }
return (0);
}

size_t  game(char **file)
{
    size_t  score;
    char    my_play;
    char    *temp;
    size_t  round_ret;
    char    my[3] = {'X', 'Y', 'Z'};
    size_t  my_i;

    score = 0;
    round_ret = 0;
    while (**file)
    {
        my_play = file[0][2];
        my_i = 0;
        while (my[my_i] != my_play && my[my_i] != 0)
            my_i++;
        round_ret = ft_round(*file);
        if (round_ret == 1)
            score += 6 + my_i + 1;
        else if (round_ret == 2)
            score += 3 + my_i + 1;
        else if (round_ret == 0)
            score += my_i + 1;
        temp = cut_input(*file);
        free(*file);
        *file = temp;
    }
    return (score);
}

int main(void)
{
    int     fd;
    char    *file;
    size_t  score;

    fd = open("input2", O_RDONLY);
    file = read_file(fd);
    score = game(&file);
    printf("%zu", score);
    close(fd);
    return (score);
}