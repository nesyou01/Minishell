/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:03:51 by ylagmah           #+#    #+#             */
/*   Updated: 2024/11/06 14:41:51 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in(char c, char const *set)
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

static char	*strdup_or_null(const char *s1)
{
	if (!s1)
		return (NULL);
	return (ft_strdup(s1));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	slen;
	char	*result;
	int		start_index;
	int		i;
	int		end_index;

	if (!s1 || !set || !*set)
		return (strdup_or_null(s1));
	slen = ft_strlen(s1);
	start_index = 0;
	end_index = slen - 1;
	while (ft_in (s1[start_index], set))
		start_index++;
	if (start_index > end_index)
		return (ft_strdup(""));
	while (ft_in (s1[end_index], set))
		end_index--;
	result = (char *)malloc((end_index - start_index + 2) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i++ + start_index <= end_index)
		result[i - 1] = s1[i - 1 + start_index];
	result[i - 1] = '\0';
	return (result);
}
