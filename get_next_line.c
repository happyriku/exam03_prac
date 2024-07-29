#include "get_next_line.h"

char *ft_strchr(char *s, int x)
{
    char c;

    if (!s)
        return (NULL);
    c = (char)x;
    while (*s != c)
    {
        if (*s == '\0')
            return (NULL);
        s++;
    }
    return (s);
}

size_t ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char    *ft_strdup(char *s1)
{
    size_t s1_len;
    char *copy_str;
    int i;

    s1_len = ft_strlen(s1);
    copy_str = (char *)malloc(sizeof(char) * (s1_len + 1));
    if (!copy_str)
        return (NULL);
    i = 0;
    while (s1[i])
    {
        copy_str[i] = s1[i];
        i++;
    }
    copy_str[i] = '\0';
    return (copy_str);
}

char    *ft_strjoin(char *s1, char *s2)
{
    int s1_len;
    int s2_len;
    char    *join_str;
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
    join_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
    if (!join_str)
        return (free(s1), NULL);
    i = 0;
    while (s1[i])
    {
        join_str[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        join_str[i] = s2[j];
        i++;
        j++;
    }
    join_str[j] = '\0';
    free(s1);
    return (join_str);
}

char *find_newline_to_line(char *read_str)
{
    int i;
    char *line;

    i = 0;
    while (read_str[i] != '\n' && read_str[i])
        i++;
    line = (char *)malloc(sizeof(char) * (i + 2));
    if (!line)
        return (free(read_str), NULL);
    i = 0;
    while (read_str[i] != '\n' && read_str[i])
    {
        line[i] = read_str[i];
        i++;
    }
    if (read_str[i] == '\n')
    {
        line[i] = read_str[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}

char *update_read_str(char *read_str, char  *line)
{
    int i;
    int j;
    char *update_str;

    i = 0;
    while (read_str[i] != '\n' && read_str[i])
        i++;
    if (!read_str[i])
        return (NULL);
    update_str = (char *)malloc(sizeof(char) * (ft_strlen(read_str) - i + 1));
    if (!update_str)
    {
        line[0] = '\0';
        return (free(read_str), NULL);
    }
    j = 0;
    i++;
    while (read_str[i])
    {
        update_str[j] = read_str[i];
        i++;
        j++;
    }
    update_str[j] = '\0';
    free(read_str);
    return (update_str);
}

char *get_next_line(int fd)
{
    char *buf;
    static char *read_str;
    ssize_t read_bytes;
    char *line;

    if (fd < 0 || BUFFER_SIZE < 0)
        return (NULL);
    buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buf)
        return (NULL);
    read_bytes = 1;
    while (!ft_strchr(read_str, '\n') && read_bytes != 0)
    {
        read_bytes = read(fd, buf, BUFFER_SIZE);
        if (read_bytes < 0)
            return (free(buf), NULL);
        buf[read_bytes] = '\0';
        if (!read_str)
        {
            read_str = ft_strdup(buf);
            if (!read_str)
                return (free(buf), NULL);
        }
        else
        {
            read_str = ft_strjoin(read_str, buf);
            if (!read_str)
                return (free(buf), NULL);
        }
    }
    free(buf);
    line = find_newline_to_line(read_str);
    if (!line)
        return (free(read_str), NULL);
    read_str = update_read_str(read_str, line);
    if (line[0] == '\0' && !read_str)
        return (NULL);
    return (line);
}