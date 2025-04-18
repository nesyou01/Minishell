/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:16:33 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/18 11:09:51 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_and(t_shell *shell, t_node *node)
{
	if (exit_status(0, 0) == 0)
		execute_tree(shell, node->r_node);
}

void	execute_or(t_shell *shell, t_node *node)
{
	if (exit_status(0, 0) != 0)
		execute_tree(shell, node->r_node);
}

void	execute_logical(t_shell *shell, t_node *node)
{
	execute_tree(shell, node->l_node);
	if (node->type == AND)
		execute_and(shell, node);
	else if (node->type == OR)
		execute_or(shell, node);
}
