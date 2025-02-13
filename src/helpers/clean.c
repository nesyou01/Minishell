/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:28:02 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/13 16:28:03 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	clear_garbage(t_list *garbage)
{
	t_list	*tmp;

	while (garbage)
	{
		tmp = garbage->next;
		free(garbage->content);
		free(garbage);
		garbage = tmp;
	}
}

void	ft_clean_cmd(t_shell *shell)
{
	if (shell->cmd_garbage)
		clear_garbage(shell->cmd_garbage);
	shell->cmd_garbage = NULL;
}

void	ft_clean_all(t_shell *shell)
{
	// TODO: close fds
	ft_clean_cmd(shell);
	if (shell->globale_garbage)
		clear_garbage(shell->globale_garbage);
	shell->globale_garbage = NULL;
}
