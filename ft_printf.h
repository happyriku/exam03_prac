#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>

int     ft_printf(const char *, ...);
void    put_decimal_number(int number);
void    put_character(char c);

# endif