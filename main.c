#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        printf("%s", line);
        if (!line)
            break ;
        free(line);
    }
    close(fd);
    return (0);
}