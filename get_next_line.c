#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	char a;

	if (!s)
		return (NULL);
	a = (char)c;
	while (*s != a)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return (s);
}

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	int s_len;
	char *str;
	int i;

	if (!s)
		s_len = 0;
	else
		s_len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *str;
	int s1_len;
	int s2_len;
	int i;
	int j;

	if (!s1)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	if (!s2)
		s2_len = 0;
	else
		s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len)
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line_help(char *save, char *buf, int fd)
{
	ssize_t	read_bytes;
	char *save_ptr;

	read_bytes = 1;
	while (!ft_strchr(save, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(buf), NULL);
		buf[read_bytes] = '\0';
		if (!save)
			save = ft_strdup(buf);
		else
		{
			save_ptr = ft_strjoin(save, buf);
			if (!save_ptr)
				return (free(buf), free(save), NULL);
			free(save);
			save = save_ptr;
		}
	}
	free(buf);
	return (save);
}

char *find_newline_to_line(char *read_part)
{
	int i;
	char *line;

	i = 0;
	while (read_part[i] != '\n' && read_part[i])
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (free(read_part), NULL);
	i = 0;
	while (read_part[i] != '\n' && read_part[i])
	{
		line[i] = read_part[i];
		i++;
	}
	if (read_part[i] == '\n')
	{
		line[i] = read_part[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_save(char *read_part, char *line)
{
	int	i;
	int	j;
	char *save;

	i = 0;
	while (read_part[i] != '\n' && read_part[i])
		i++;
	if (!read_part[i])
		return (NULL);
	save = (char *)malloc(sizeof(char) * (ft_strlen(read_part) - i + 1));
	if (!save)
		return (free(save), free(line), NULL);
	j = 0;
	i++;
	while (read_part[i])
	{
		save[i] = read_part[i];
		i++;
	}
	save[i] = '\0';
	return (save);
}

char	*get_next_line(int fd)
{
	static char *save;
	char		*buf;
	char		*line;
	char		*read_part;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	read_part = get_next_line_help(save, buf, fd);
	if (!read_part)
		return (free(save), NULL);
	line = find_newline_to_line(read_part);
	if (!line)
		return (NULL);
	save = update_save(read_part, line);
	if (!save)
		return (NULL);
	free(read_part);
	return (line);
}

int main(void)
{
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
        printf("%s", line);
		if (!line)
			return (0);
		free(line);
	}
	close(fd);
	return (0);
}