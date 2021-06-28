#include "get_next_line.h"

int ft_free_and_return(char **keep, int ret)
{
	ft_free(keep);
	return (ret);
}

int		ft_find_newline(const char *s, int c)
{
	int		i;
	char	*ret;

	i = -1;
	ret = (char *)s;
	while (ret[++i])
		if (ret[i] == (char)c)
			return (i);
	return (-1);
}

int		ft_fill_line(char **keep, char **line, int fd)
{
	char	*tmp;
	int		idx;

	idx = ft_find_newline(keep[fd], '\n');
	if (idx != -1 && keep[fd][idx] == '\n')
	{
		if (!(*line = ft_substr(keep[fd], 0, idx)))
			return (ft_free_and_return(keep, -1));
		if (!(tmp = ft_substr(keep[fd], idx + 1, ft_strlen(keep[fd]))))
			return (ft_free_and_return(keep, -1));
		ft_free(&keep[fd]);
		keep[fd] = tmp;
	}
	else
	{
		if (!(*line = ft_strdup(keep[fd])))
			return (ft_free_and_return(keep, -1));
		ft_free(&keep[fd]);
		return (0);
	}
	return (1);
}

char	*ft_update_static(char **keep, char *buf, int fd)
{
	char *tmp;

	if (!keep[fd])
	{
		if (!(keep[fd] = ft_strdup("")))
		{
			if (buf)
				free(buf);
			return (NULL);
		}
	}
	if (!(tmp = ft_strjoin(keep[fd], buf)))
	{
		ft_free(&keep[fd]);
		free(buf);
		return (NULL);
	}
	ft_free(&keep[fd]);
	keep[fd] = tmp;
	return (keep[fd]);
}

int		get_next_line(int fd, char **line)
{
	int			input;
	char		*buf;
	static char	*keep[FOPEN_MAX];

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > FOPEN_MAX || !line
			|| !(buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (ft_free_and_return(keep, -1));
	while ((input = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[input] = '\0';
		if (!(keep[fd] = ft_update_static(keep, buf, fd)))
			return (-1);
		if (ft_find_newline(keep[fd], '\n') > -1)
			break ;
	}
	free(buf);
	if (input < 0)
		return (-1);
	else if (input == 0 && !keep[fd])
	{
		if (!(*line = ft_strdup("")))
			return (-1);
		return (0);
	}
	return (ft_fill_line(keep, line, fd));
}
