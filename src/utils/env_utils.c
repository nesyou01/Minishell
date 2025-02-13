/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:35:15 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/13 16:26:54 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	get_key_size(char *str)
{
	size_t	size;

	size = 0;
	while (str[size] && str[size] != '=')
		size++;
	return (size);
}

char	*ft_get_env_key(t_shell *shell, char *str)
{
	size_t	size;
	size_t	i;
	char	*result;

	size = get_key_size(str);
	result = (char *) ft_malloc_globale(shell, (size + 1) * sizeof(char));
	i = 0;
	while (i < size)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

t_env	*ft_parse_env(t_shell *shell, char *str, char *key)
{
	t_env	*result;
	char	*value;

	result = (t_env *) ft_malloc_globale(shell, sizeof(t_env));
	value = ft_strchr(str, '=');
	if (value)
		result->value = ft_strdup_globale(shell, value + 1);
	if (!key)
		result->key = ft_get_env_key(shell, str);
	else
		result->key = key;
	result->next = NULL;
	return (result);
}

t_env	*ft_last_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_env	*ft_get_env(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && ft_strcmp(tmp->key, key) != 0)
		tmp = tmp->next;
	return (tmp);
}
