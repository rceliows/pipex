/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceliows <rceliows@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:40 by rceliows          #+#    #+#             */
/*   Updated: 2025/05/12 18:10:42 by rceliows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_conversion(char specifier, va_list args)
{
	if (specifier == 'c')
	{
		ft_putchar(va_arg(args, int));
		return (1);
	}
	else if (specifier == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (specifier == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (specifier == 'u')
		return (ft_putuns(va_arg(args, unsigned int)));
	else if (specifier == 'x')
		return (ft_puthex(va_arg(args, unsigned int), 0));
	else if (specifier == 'X')
		return (ft_puthex(va_arg(args, unsigned int), 1));
	else if (specifier == '%')
	{
		ft_putchar('%');
		return (1);
	}
	return (-1);
}

int	ft_printf(const char *s, ...)
{
	int		len;
	int		conversion_result;
	va_list	args;

	len = 0;
	if (!s)
		return (-1);
	va_start(args, s);
	while (*s)
	{
		if (*s == '%' && *(s + 1))
		{
			conversion_result = handle_conversion(*++s, args);
			if (conversion_result == -1)
				return (-1);
			len += conversion_result;
		}
		else
			len += ft_putchar(*s);
		s++;
	}
	va_end(args);
	return (len);
}
