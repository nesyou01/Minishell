/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:28:05 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/24 20:41:51 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute(t_shell *shell, t_node *node)
{
	while (node)
	{
		if (ft_expand_node_vars(shell, node))
			return ;
		// if (node->type != COMMAND)
		// {
			if (node->l_node)
				printf("%s <===", node->l_node->content);
			printf(" %s ", node->content);
			if (node->r_node)
				printf("===> %s", node->l_node->content);
			printf("\n");
		// }
		node = node->next;
	}
}
