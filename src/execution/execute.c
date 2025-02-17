/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:28:05 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/17 11:09:03 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute(t_shell *shell, t_node *node)
{
	if (!node)
		return ;
	// TODO
	while (node)
	{
		if (ft_expand_node_vars(shell, node))
			return ;
		printf("--> %s -- %d\n", node->content, node->type);
		node = node->next;
	}
}
