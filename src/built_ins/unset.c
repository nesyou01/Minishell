/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:34:35 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/13 16:28:18 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_shell *shell, char *var)
{
	t_env	*tmp;

	if (!var || !shell->env)
		return ;
	tmp = ft_get_env(shell->env, var);
	if (!tmp)
		return ;
	tmp = shell->env;
	if (!ft_strcmp(tmp->key, var))
	{
		shell->env = tmp->next;
		return ;
	}
	while (ft_strcmp(tmp->next->key, var))
		tmp = tmp->next;
	tmp->next = tmp->next->next;
}
