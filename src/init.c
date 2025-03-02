/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:35:36 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/02 15:26:43 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_init(t_shell *shell, char **env)
{
	t_env	*last;

	shell->env = NULL;
	shell->envp = env;//just for testing the env !
	if (!env)
		return ;
	shell->cmd_garbage = NULL;
	shell->globale_garbage = NULL;
	shell->env = ft_parse_env(shell, *env, NULL);
	env++;
	while (*env)
	{
		last = ft_last_env(shell->env);
		last->next = ft_parse_env(shell, *env, NULL);
		env++;
	}
}
