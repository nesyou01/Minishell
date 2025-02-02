/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:34:38 by ylagmah           #+#    #+#             */
/*   Updated: 2025/01/24 11:34:39 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_export(t_shell *shell, char *var)
{
	t_env	*env;
	char	*key;
	char	*value;

	if (!var)
		return (ft_env(shell));
	key = ft_get_env_key(var);
	if (!key)
		return ;
	env = ft_get_env(shell->env, key);
	if (!env)
		ft_last_env(shell->env)->next = ft_parse_env(var, key);
	else
	{
		value = ft_strchr(var, '=');
		free(env->value);
		if (value)
			env->value = ft_strdup(value + 1);
		else
			env->value = NULL;
	}
}
