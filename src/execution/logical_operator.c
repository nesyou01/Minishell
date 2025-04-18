/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:16:33 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/18 11:06:52 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_and(t_shell *shell, t_node *node)
{
	int	r_status;

	if (exit_status(0, 0) == 0)
	{
		execute_tree(shell, node->r_node);
		r_status = exit_status(0, 0);
		exit_status(1, r_status);
	}
}

void	execute_or(t_shell *shell, t_node *node)
{
	int	r_status;

	if (exit_status(0, 0) != 0)
	{
		execute_tree(shell, node->r_node);
		r_status = exit_status(0, 0);
		exit_status(1, r_status);
	}
}

void	execute_logical(t_shell *shell, t_node *node)
{
	if (!node || !node->l_node || !node->r_node)
		return ;
	execute_tree(shell, node->l_node);
	if (node->type == AND)
		execute_and(shell, node);
	else if (node->type == OR)
		execute_or(shell, node);
}
