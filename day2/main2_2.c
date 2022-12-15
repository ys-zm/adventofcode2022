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
    char    outcome;
    char    opp[3] = {'A', 'B', 'C'};
    char    my[3] = {'X', 'Y', 'Z'};
    
    opponent_play = file[0];
    outcome = file[2];
    if (outcome == 'X') //LOSE
    {
        if (opponent_play == 'A')
            return (3); //for rock i play 'scissors' 'Z' 3
        else if (opponent_play == 'B')
            return (1); //for paper i play 'rock' 'X' 1
        else if (opponent_play == 'C')
            return (2); //for scissors i play 'paper' 'Y' 2
    }
    else if (outcome == 'Y') //DRAW
    {
        if (opponent_play == 'A')
            return (1); //for rock i play 'rock' 'X' 1
        else if (opponent_play == 'B')
            return (2); //for paper i play 'paper' 'Y' 2
        else if (opponent_play == 'C')
            return (3); //for scissors i play 'scrissors' 'Z' 3
    }
    else if (outcome == 'Z') //WIN
    {
        if (opponent_play == 'A')
            return (2); //for rock i play 'paper' 'Z' 2
        else if (opponent_play == 'B')
            return (3); //for paper i play 'scissors' 'X' 3
        else if (opponent_play == 'C')
            return (1); //for scissors i play 'rock' 'Y' 1
    }
return (0);
}

size_t  game(char **file)
{
    size_t  score;
    char    outcome;
    char    *temp;
    size_t  my_play;

    score = 0;
    my_play = 0;
    while (**file)
    {
        outcome = file[0][2];
        my_play = ft_round(*file);
        if (outcome == 'X')
            score += 0 + my_play; //my play;
        else if (outcome == 'Y')
            score += 3 + my_play;
        else if (outcome == 'Z')
            score += 6 + my_play;
        temp = cut_input(*file);
        free(*file);
        *file = temp;
    }
    return (score);
}

//part2
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