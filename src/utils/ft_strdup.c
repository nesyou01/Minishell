/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:12:20 by ylagmah           #+#    #+#             */
/*   Updated: 2024/11/12 21:04:32 by ylagmah          ###   ########.fr       */
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
