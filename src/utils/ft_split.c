/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:49:56 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/15 12:49:57 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static char	*split_to_c(t_shell *shell, char const *s, char c)
{
	size_t	ri;
	char	*result;
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	ri = 0;
	result = (char *) ft_malloc (shell, (len + 1) * sizeof(char));
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

char	**ft_split(t_shell *shell, char const *s, char c)
{
	char	**result;
	size_t	ri;
	size_t	size;

	if (!s)
		return (NULL);
	ri = 0;
	size = split_size(s, c);
	result = (char **) ft_malloc(shell, sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	while (ri++ < size)
	{
		while (*s && *s == c)
			s++;
		result[ri - 1] = split_to_c(shell, s, c);
		while (*s && *s != c)
			s++;
	}
	result[ri - 1] = NULL;
	return (result);
}
