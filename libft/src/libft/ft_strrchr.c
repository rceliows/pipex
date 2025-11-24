/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceliows <rceliows@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:50:16 by rceliows          #+#    #+#             */
/*   Updated: 2025/04/16 13:50:18 by rceliows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (s[i])
	{
		if (s[i] == (char)c)
			last = i;
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	if (last == -1)
		return (NULL);
	return ((char *)&s[last]);
}
