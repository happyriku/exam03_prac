#include "ft_printf.h"

void    put_decimal_number(int number)
{  
    if (number < 0)
    {
        if (number == -2147483648)
        {
            write(1, "-2147483648", 11);
            return ;
        }
        write(1, "-", 1);
        number *= -1;
    }
    if (number >= 10)
    {
        put_decimal_number(number / 10);
        put_decimal_number(number % 10);
    }
    else if (number < 9)
        put_character(number + '0');
    return ;
}