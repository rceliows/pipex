/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceliows <rceliows@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:47 by rceliows          #+#    #+#             */
/*   Updated: 2025/05/12 18:10:49 by rceliows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putchar(char c);
int	ft_puthex(unsigned int n, int uppercase);
int	ft_putnbr(int n);
int	ft_putptr(void *ptr);
int	ft_putstr(char *s);
int	ft_putuns(unsigned int n);

#endif
