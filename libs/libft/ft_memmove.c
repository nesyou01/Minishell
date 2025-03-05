/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:35:39 by ylagmah           #+#    #+#             */
/*   Updated: 2024/11/12 20:43:35 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	s = (char *)src;
	d = (char *)dst;
	i = 0;
	if (d > s)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
