/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceliows <rceliows@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:51:48 by rceliows          #+#    #+#             */
/*   Updated: 2025/04/16 13:51:50 by rceliows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*copy_word(const char *s, size_t len)
{
	char	*word;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, len + 1);
	return (word);
}

static void	free_all(char **res, int i)
{
	while (i >= 0)
	{
		free(res[i]);
		i--;
	}
}

static void	*array_formation(char **res, const char *s, char c)
{
	int			i;
	const char	*start;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			start = s;
			while (*s && *s != c)
				s++;
			res[i] = copy_word(start, s - start);
			if (!res[i])
				return (free_all(res, i - 1), NULL);
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char		**res;
	int			words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	res = array_formation(res, s, c);
	if (!res)
		return (NULL);
	return (res);
}
