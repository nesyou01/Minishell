/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:28:02 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/12 00:14:20 by ylagmah          ###   ########.fr       */
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

void	ft_close_all(t_node *node)
{
	t_file	*tmp;

	node = ft_head_node(node);
	while (node)
	{
		tmp = node->io;
		while (tmp)
		{
			if (tmp->fd != -1)
				close(tmp->fd);
			tmp = tmp->next;
		}
		node = node->next;
	}
}

void	ft_clean_cmd(t_shell *shell, t_node *node)
{
	ft_close_all(node);
	if (shell->cmd_garbage)
		clear_garbage(shell->cmd_garbage);
	shell->cmd_garbage = NULL;
}

void	ft_clean_all(t_shell *shell, t_node *node)
{
	ft_clean_cmd(shell, node);
	if (shell->globale_garbage)
		clear_garbage(shell->globale_garbage);
	shell->globale_garbage = NULL;
}

void	ft_exit(t_shell *shell, t_node *node, int status)
{
	ft_close_all(node);
	ft_clean_all(shell, node);
	exit(status);
}
