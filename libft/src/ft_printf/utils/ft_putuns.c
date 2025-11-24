/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceliows <rceliows@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:37:52 by rceliows          #+#    #+#             */
/*   Updated: 2025/05/13 16:37:54 by rceliows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/ft_printf.h"

int	ft_putuns(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_putuns(n / 10);
	count += ft_putchar((n % 10) + '0');
	return (count);
}
