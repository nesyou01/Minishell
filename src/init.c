/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:35:36 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/11 14:58:48 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_init(t_shell *shell, char **env)
{
	t_env	*last;

	if (!env || !*env)
		return (1);
	shell->env = NULL;
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
	return (0);
}

int	ft_any_not_tty()
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || !isatty(STDERR_FILENO))
		return (ft_perror("In/Out not connected to a terminal"), 1);
	return (0);
}
