/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:53:41 by ylagmah           #+#    #+#             */
/*   Updated: 2024/11/12 21:20:02 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	y;

	if (!*needle)
		return ((char *)haystack);
	y = 0;
	i = 0;
	while (i < len && haystack[i])
	{
		while (haystack[i + y] && haystack[i + y] == needle[y] && i + y < len)
			y++;
		if (!needle[y])
			return ((char *)((haystack + i)));
		y = 0;
		i++;
	}
	return (NULL);
}
