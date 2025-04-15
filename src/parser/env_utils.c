/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:13:59 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/15 13:58:51 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	get_env_size(t_env *env)
{
	size_t	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**ft_get_all_env(t_shell *shell)
{
	char	**result;
	size_t	i;
	t_env	*tmp;

	i = 0;
	tmp = shell->env;
	result = ft_malloc(shell, sizeof(char *) * (get_env_size(shell->env) + 1));
	while (tmp)
	{
		result[i++] = ft_strjoin(shell,
				ft_strjoin(shell, tmp->key, "="), tmp->value);
		tmp = tmp->next;
	}
	result[i] = NULL;
	return (result);
}

static int	is_concat(char *key_value)
{
	while (*key_value && *key_value != '=')
	{
		if (*key_value == '+')
			return (1);
		key_value++;
	}
	return (0);
}

void	set_env(t_shell *shell, t_env *env, char *key_value, char *key)
{
	t_env	*last;
	char	*value;

	if (!env)
	{
		last = ft_last_env(shell->env);
		last->next = ft_parse_env(shell, key_value, key);
	}
	else
	{
		value = ft_strchr(key_value, '=');
		if (value)
		{
			if (is_concat(key_value))
				env->value = ft_strjoin_globale(shell, env->value, value + 1);
			else
				env->value = ft_strdup_globale(shell, value + 1);
		}
	}
}
