/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:12:59 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/21 01:47:57 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isvalid_var(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	ft_is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	get_var_end(char *s)
{
	int	i;

	i = 1;
	if (s[i] == '?')
		return (i);
	while (s[i] && ft_isvalid_var(s[i]))
		i++;
	if (s[i])
		i--;
	return (i);
}
