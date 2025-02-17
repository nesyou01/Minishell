/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:35:15 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/17 10:50:12 by ylagmah          ###   ########.fr       */
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
