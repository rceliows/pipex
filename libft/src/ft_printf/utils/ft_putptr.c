/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceliows <rceliows@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:37:40 by rceliows          #+#    #+#             */
/*   Updated: 2025/05/13 16:37:41 by rceliows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/ft_printf.h"

static int	ft_putptr_hex(unsigned long n, char *hex)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += ft_putptr_hex(n / 16, hex);
	count += ft_putchar(hex[n % 16]);
	return (count);
}

int	ft_putptr(void *ptr)
{
	int				count;
	char			*hex;
	unsigned long	n;

	if (ptr == NULL)
		return (ft_putstr("(nil)"));
	n = (unsigned long)ptr;
	hex = "0123456789abcdef";
	count = ft_putstr("0x");
	count += ft_putptr_hex(n, hex);
	return (count);
}
