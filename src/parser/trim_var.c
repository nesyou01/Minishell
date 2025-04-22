/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:50:38 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/22 01:32:13 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	total_size(char *old)
{
	size_t	i;
	size_t	size;

	size = 0;
	i = 0;
	while (old[i] && ft_isspace(old[i]))
		i++;
	while (old[i])
	{
		if (!ft_isspace(old[i]))
		{
			if (i >= 1 && ft_isspace(old[i - 1]))
				size++;
			size++;
		}
		i++;
	}
	return (size);
}

char	*ft_trim_var(t_shell *shell, char *old)
{
	char	*result;
	size_t	i;
	size_t	x;

	if (!old)
		return (NULL);
	i = 0;
	x = 0;
	result = ft_malloc(shell, total_size(old) + 1);
	while (old[i] && ft_isspace(old[i]))
		i++;
	while (old[i])
	{
		if (!ft_isspace(old[i]))
		{
			if (x > 0 && ft_isspace(old[i - 1]))
				result[x++] = ' ';
			result[x++] = old[i];
		}
		i++;
	}
	result[x] = '\0';
	return (result);
}
