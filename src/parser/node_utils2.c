/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:12:17 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/22 01:12:55 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*ft_new_node_str(t_shell *shell, char *str)
{
	t_node	*list;

	list = (t_node *) ft_malloc(shell, sizeof(t_node));
	list->content = str;
	list->type = EMPTY_CMD;
	list->next = NULL;
	list->filter = NULL;
	list->prev = NULL;
	list->l_node = NULL;
	list->r_node = NULL;
	list->io = NULL;
	list->taken = 0;
	return (list);
}
