/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:16:33 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/26 18:14:12 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_logical(t_shell *shell, t_node *node)
{
	int	l_status;

	if (!node || !node->l_node || !node->r_node)
		return ;
	execute_tree(shell, node->l_node);
	l_status = shell->exit;
	if (node->type == AND)
	{
		if (l_status == 0)
			execute_tree(shell, node->r_node);
	}
	else if (node->type == OR)
	{
		if (l_status != 0)
			execute_tree(shell, node->r_node);
	}
}
