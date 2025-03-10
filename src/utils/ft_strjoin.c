/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:50:43 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/10 23:24:35 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin(t_shell *shell, char const *s1, char const *s2)
{
	char	*result;
	size_t	s1len;
	size_t	s2len;
	size_t	dstsize;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(shell, s2));
	if (!s2)
		return (ft_strdup(shell, s1));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	dstsize = s1len + s2len + 1;
	result = (char *) ft_malloc(shell, dstsize);
	ft_strlcpy(result, s1, s1len + 1);
	ft_strlcat(result, s2, dstsize);
	return (result);
}

char	*ft_strjoin_globale(t_shell *shell, char const *s1, char const *s2)
{
	char	*result;
	size_t	s1len;
	size_t	s2len;
	size_t	dstsize;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_globale(shell, s2));
	if (!s2)
		return (ft_strdup_globale(shell, s1));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	dstsize = s1len + s2len + 1;
	result = (char *) ft_malloc_globale(shell, dstsize);
	ft_strlcpy(result, s1, s1len + 1);
	ft_strlcat(result, s2, dstsize);
	return (result);
}
