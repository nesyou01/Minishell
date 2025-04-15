/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:49:47 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/15 12:49:49 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strnstr2(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	y;

	if (!*needle)
		return ((char *)haystack);
	y = 0;
	i = 0;
	while (i < len && haystack[i])
	{
		while (haystack[i + y]
			&& ft_tolower(haystack[i + y]) == needle[y] && i + y < len)
			y++;
		if (!needle[y])
			return ((char *)((haystack + i)));
		y = 0;
		i++;
	}
	return (NULL);
}
