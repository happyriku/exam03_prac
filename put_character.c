#include "ft_printf.h"

void    put_character(char c)
{
    write(1, &c, 1);
    return ;
}
