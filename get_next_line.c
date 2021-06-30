#include "get_next_line.h"

static int	ft_strnl(char *aux)
{
	int	i;

	i = 0;
	while (*(aux + i) && *(aux + i) != '\n')
		i++;
	if ((int)ft_strlen(aux) == i)
		return (-1);
	return (i);
}

static int	ft_free(char **s)
{
	free(*s);
	*s = NULL;
	return (-1);
}

static ssize_t	ft_reader(int fd, char **content, ssize_t *len_read)
{
	char	*buf;
	char	*aux;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (-1);
	while (ft_strnl(*content) < 0 && *len_read > 0)
	{
		*len_read = read(fd, buf, BUFFER_SIZE);
		if (*len_read == -1)
			break ;
		*(buf + *len_read) = '\0';
		aux = ft_strdup(*content);
		free(*content);
		if (!aux)
			return (ft_free(&buf));
		*content = ft_strjoin(aux, buf);
		free(aux);
		if (!*content)
			return (ft_free(&buf));
	}
	free(buf);
	return (*len_read);
}

int	ft_line_generator(char *content, char **line, char **leftover)
{
	int		index;
	ssize_t	len;

	index = ft_strnl(content);
	len = ft_strlen(content);
	if (index == -1)
		index = ft_strlen(content);
	*line = ft_substr(content, 0, index);
	if (!*line)
		return (ft_free(&content));
	if (index < (int)ft_strlen(content) - 1)
		*leftover = ft_substr(content, index + 1, len);
	free(content);
	if (!*leftover)
		return (-1);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*leftover;
	char		*content;
	ssize_t		len_read;

	if (!line || fd < 0 || fd > 4096 || BUFFER_SIZE <= 0)
		return (-1);
	if (leftover)
	{
		content = ft_strdup(leftover);
		free(leftover);
		leftover = NULL;
	}
	else
		content = ft_strdup("");
	if (!content)
		return (-1);
	len_read = 1;
	if (ft_reader(fd, &content, &len_read) == -1)
	{
		free(content);
		return (-1);
	}
	return (ft_line_generator(content, line, &leftover) && len_read > 0);
}
