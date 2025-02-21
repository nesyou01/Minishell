/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:28:05 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/21 15:36:39 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute(t_shell *shell, t_execute *exe)
{
	t_node	*node;
	t_list	*lst;

	// TODO
	node = exe->node;
	while (node)
	{
		if (ft_expand_node_vars(shell, node))
			return ;
		printf("%s\n", node->filter);
		lst = ft_split(shell, node->content, node->filter);
		while (lst)
		{
			printf("%s\n", (char *)lst->content);
			lst = lst->next;
		}
		node = node->next;
	}
}

// printf("--> %s(%d) [input: ", node->content, node->type);
// 		while (node->in)
// 		{
// 			printf("%s ", node->in->path);
// 			node->in = node->in->next;
// 		}
// 		printf("]   [output: ");
// 		while (node->out)
// 		{
// 			printf("%s ", node->out->path);
// 			node->out = node->out->next;
// 		}
// 		printf("]   [here_doc: ");
// 		while (node->here_doc)
// 		{
// 			printf("%s ", node->here_doc->path);
// 			node->here_doc = node->here_doc->next;
// 		}
// 		printf("]\n");