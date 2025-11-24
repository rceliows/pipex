/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceliows <rceliows@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:51:39 by rceliows          #+#    #+#             */
/*   Updated: 2025/04/16 13:51:41 by rceliows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	is_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	n;
	size_t	start;
	size_t	end;
	char	*a;

	n = 0;
	start = 0;
	if (!s1)
		return (NULL);
	end = ft_strlen(s1);
	if (start == end)
		return (ft_strdup(""));
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	end--;
	while (is_in_set(s1[end], set) && end > start)
		end--;
	a = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!a)
		return (NULL);
	while (start <= end)
		a[n++] = s1[start++];
	a[n] = '\0';
	return (a);
}
