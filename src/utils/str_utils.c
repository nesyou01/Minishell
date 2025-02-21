/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:12:30 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/21 15:19:33 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_safe_strlen(char *str)
{
	if (!str)
		return (0);
	return (ft_strlen(str));
}

char	*ft_repeat(t_shell *shell, size_t len, char c)
{
	char	*result;
	size_t	i;

	result = ft_malloc(shell, (len + 1) * sizeof(char));
	i = 0;
	while (i < len)
		result[i++] = c;
	result[i] = '\0';
	return (result);
}

int	ft_index_of(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
