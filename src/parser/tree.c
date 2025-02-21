/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:33:22 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/21 10:57:23 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_node	*ft_get_first_not_taken(t_node *node)
{
	while (node && node->taken)
	{
		node = node->next;
	}
	if (node)
		node->taken = 1;
	return (node);
}

t_node	*ft_to_tree(t_node *node)
{
	if (!node)
		return (NULL);
	if (node->type >= 100)
	{
		node->r_node = ft_to_tree(ft_get_first_not_taken(node->next));
		node->l_node = ft_to_tree(ft_get_first_not_taken(node->next));
	}
	return (node);
}
