/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:56:23 by ylagmah           #+#    #+#             */
/*   Updated: 2025/01/31 23:49:42 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substr(t_shell *shell, char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	startlen;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(shell, ""));
	startlen = ft_strlen(s + start);
	if (startlen < len)
		len = startlen;
	result = (char *) ft_malloc (shell, (len + 1) * sizeof(char));
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}
