#include "get_next_line.h"

char    *check_rem(char *rem, char **line)
{
    char    *p_n;
    
    p_n = NULL;
    if (rem)
        if ((p_n = ft_strchr(rem, '\n')))
        {
            *p_n = '\0';
            *line = ft_strdup(rem);
            ft_strcpy(rem, ++p_n);
        }
        else
        {
            *line = ft_strdup(rem);
            //clear
        }
        else 
        //*line = bzero(1)? заполнение нулями, ну нужно еще аллоцировать память 
        return(p_n);
}

int get_next_line(int fd, char **line)
{
    char        buf[BUFFER_SIZE + 1];
    static char *rem;
    int         bwr;
    char        *p_n;
    char        *tmp;

    p_n = check_rem(rem, line);
    while (!p_n && (bwr = read(fd, buf, BUFFER_SIZE)))
    {
        buf[bwr] = '/0';
        if ((p_n = ft_strchr(buf, '\n')))
        {
            *p_n = '\0';
            rem = ft_strdup(++p_n);
        }
        tmp = *line;
        *line = ft_strjoin(*line, buf);
        free(tmp);
    }
    if (bwr || ft_strlen(rem) || ft_strlen(*line))
        return (1);
    else 
        return (0);
//написать условие для -1 (произошла ошибка)
}