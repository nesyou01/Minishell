/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:06:43 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/18 15:33:44 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_line(char *s1)
{
	char	*result;
	size_t	size;
	size_t	i;

	if (!s1)
		return (NULL);
	i = 0;
	size = ft_strlen(s1);
	if (size == 0)
		return (NULL);
	result = (char *) malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (i < size)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	i;
	size_t	src_len;

	if (!dst && src && dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while (src[i] && i < (dstsize - dst_len - 1))
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = '\0';
	return (dst_len + src_len);
}

static size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*ft_strjoin_line(char *s1, char *s2, size_t s2len)
{
	char	*result;
	size_t	s1len;
	size_t	dstsize;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_line(s2));
	if (!s2)
		return (s1);
	s1len = ft_strlen(s1);
	dstsize = s1len + s2len + 1;
	result = (char *) malloc(dstsize * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, s1len + 1);
	ft_strlcat(result, s2, dstsize);
	free(s1);
	return (result);
}
