/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:34:35 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/22 15:34:10 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	unset_var(t_shell *shell, char *key)
{
	t_env	*tmp;

	if (*key == '-' && key[1])
		return (ft_perror3("unset", key, "invalid options"), 1);
	if (!ft_is_valid_key(key))
		return (ft_perror3("unset", key, "not a valid identifier"), 1);
	tmp = ft_get_env(shell->env, key);
	if (!tmp)
		return (0);
	tmp = shell->env;
	if (!ft_strcmp(tmp->key, key))
	{
		shell->env = tmp->next;
		return (0);
	}
	while (ft_strcmp(tmp->next->key, key))
		tmp = tmp->next;
	tmp->next = tmp->next->next;
	return (0);
}

int	ft_unset(t_shell *shell, t_command *cmd)
{
	int		i;
	int		is_fail;

	is_fail = 0;
	i = 1;
	while (cmd->argv[i])
	{
		if (!is_fail)
			is_fail = unset_var(shell, cmd->argv[i++]);
		else
			unset_var(shell, cmd->argv[i++]);
	}
	return (is_fail);
}
