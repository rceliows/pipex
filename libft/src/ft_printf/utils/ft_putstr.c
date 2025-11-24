/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceliows <rceliows@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:37:46 by rceliows          #+#    #+#             */
/*   Updated: 2025/05/13 16:37:47 by rceliows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/ft_printf.h"

int	ft_putstr(char *s)
{
	int	count;

	count = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (*s)
		count += ft_putchar(*s++);
	return (count);
}
