#include "ft_printf.h"

void    ft_printf_help(const char *s, va_list args)
{
    int i;

    i = 0;
    if (s[i] == 'd')
        put_decimal_number(va_arg(args, int));
    else if (s[i] == 's')
        printf("%s", va_arg(args, char *));
    else if (s[i] == 'x')
        printf("%x", va_arg(args, int));
}

void    print_string(const char *s)
{
    int i;

    i = 0;
    put_character(*s);
}

int ft_printf(const char *s, ...)
{
    va_list args;
    int     i;

    va_start(args, s);
    i = 0;
    while (s[i])
    {
        if (s[i] == '%')
        {
            i++;
            ft_printf_help(&s[i], args);
        }
        else
            print_string(&s[i]);
        i++;
    }
    return (0);
}

int main(void)
{
    int value;
    int x;

    x = 123;
    value = ft_printf("%d\n", x);
    value = ft_printf("%d\n", -2147483648);
    value = ft_printf("%d\n", -2);
    // value = ft_printf("%s", "42Tokyo");
    return (0);
}