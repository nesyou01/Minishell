/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:35:15 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/19 22:00:48 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_env_value(t_shell *shell, char *key)
{
	t_env	*env;

	env = ft_get_env(shell->env, key);
	if (!env)
		return (NULL);
	return (env->value);
}

static int	is_all_alnum(char *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int	ft_is_valid_key(char *str)
{
	return (str && *str
		&& is_all_alnum(str)
		&& (ft_isalpha(*str) || *str == '_'));
}
