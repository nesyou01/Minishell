/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:08:03 by ylagmah           #+#    #+#             */
/*   Updated: 2025/01/22 13:23:24 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	split_size(char const *s, char c)
{
	size_t	i;
	size_t	size;

	size = 1;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i])
				size++;
		}
		else
			i++;
	}
	return (size);
}

static char	*split_to_c(char const *s, char c)
{
	size_t	ri;
	char	*result;
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	ri = 0;
	result = (char *) malloc (len + 1);
	if (!result)
		return (NULL);
	while (*s && *s != c)
	{
		result[ri] = *s;
		ri++;
		s++;
	}
	result[ri] = '\0';
	return (result);
}

static void	*free_and_return(char **result, int i)
{
	while (--i >= 0)
		free(result[i]);
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	ri;
	size_t	size;

	if (!s)
		return (NULL);
	ri = 0;
	size = split_size(s, c);
	result = (char **) malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	while (ri++ < size)
	{
		while (*s && *s == c)
			s++;
		result[ri - 1] = split_to_c(s, c);
		if (!result[ri - 1])
			return (free_and_return(result, ri));
		while (*s && *s != c)
			s++;
	}
	result[ri - 1] = NULL;
	return (result);
}
