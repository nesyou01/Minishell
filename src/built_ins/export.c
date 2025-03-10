/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:34:38 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/10 23:34:38 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (env->value)
			printf("declare -x %s=%s\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
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

static void	set_env(t_shell *shell, char *key, char *key_value)
{
	t_env	*env;
	char	*value;
	t_env	*last;

	env = ft_get_env(shell->env, key);
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

int	ft_export(t_shell *shell, t_command *cmd)
{
	char	*key;
	char	*key_value;

	key_value = cmd->argv[1];
	if (!key_value)
		return (print_env(shell), 1);
	if (*key_value == '-' && key_value[1])
		return (ft_perror2("invalid options", key_value), 1);
	key = ft_get_env_key(shell, key_value);
	if (!ft_is_valid_key(key))
		return (ft_perror2("invalid identifier", key), 1);
	set_env(shell, key, key_value);
	if (key_value && cmd->argv[2])
		return (ft_perror2("invalid identifier", cmd->argv[2]), 1);
	return (0);
}
