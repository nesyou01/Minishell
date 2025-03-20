/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:34:38 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/10 23:55:13 by ylagmah          ###   ########.fr       */
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
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
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

static void	set_env(t_shell *shell, t_env *env, char *key_value, char *key)
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

static int	handle_env(t_shell *shell, char *key_value)
{
	t_env	*env;
	char	*key;

	if (!*key_value)
		return (0);
	key = ft_get_env_key(shell, key_value);
	if (!ft_is_valid_key(key))
		return (ft_perror2("invalid identifier", key), 1);
	env = ft_get_env(shell->env, key);
	set_env(shell, env, key_value, key);
	return (0);
}

static int	should_print(char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (argv[i] && argv[i][0])
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_shell *shell, t_command *cmd)
{
	int		is_fail;
	int		i;

	i = 1;
	if (should_print(cmd->argv))
		return (print_env(shell), 1);
	is_fail = 0;
	while (cmd->argv[i])
	{
		if (!is_fail)
			is_fail = handle_env(shell, cmd->argv[i++]);
		else
			handle_env(shell, cmd->argv[i++]);
	}
	return (is_fail);
}
