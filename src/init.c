/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:35:36 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/13 14:40:55 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_init(t_shell *shell, char **env)
{
	shell->env = NULL;
	if (!env)
		return ;
	shell->cmd_garbage = NULL;
	shell->globale_garbage = NULL;
	shell->file = NULL;
	shell->env = ft_parse_env(shell, *env, NULL);
	env++;
	while (*env)
	{
		ft_last_env(shell->env)->next = ft_parse_env(shell, *env, NULL);
		env++;
	}
}
