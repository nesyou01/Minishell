/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:34:38 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/04 15:17:07 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_export(t_shell *shell, char *var)
{
	t_env	*env;
	t_env	*last;
	char	*key;
	char	*value;

	if (!var)
		return (ft_env(shell));
	key = ft_get_env_key(shell, var);
	if (!key)
		return ;
	env = ft_get_env(shell->env, key);
	if (!env)
	{
		last = ft_last_env(shell->env);
		last->next = ft_parse_env(shell, var, key);
	}
	else
	{
		value = ft_strchr(var, '=');
		if (value)
			env->value = ft_strdup(shell, value + 1);
		else
			env->value = NULL;
	}
}
