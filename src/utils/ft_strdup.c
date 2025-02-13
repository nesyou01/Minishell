/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:12:20 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/13 16:26:51 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup(t_shell *shell, const char *s1)
{
	char	*result;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(s1);
	result = (char *) ft_malloc(shell, (size + 1) * sizeof(char));
	while (i < size)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strdup_globale(t_shell *shell, const char *s1)
{
	char	*result;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(s1);
	result = (char *) ft_malloc_globale(shell, (size + 1) * sizeof(char));
	while (i < size)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
