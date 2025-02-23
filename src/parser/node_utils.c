/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:34:22 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/23 09:21:08 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_node	*ft_last_node(t_node *lst)
{
	t_node	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_add_node_start(t_node **lst, t_node *new)
{
	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	(*lst)->prev = new;
	new->next = *lst;
	*lst = new;
}

t_node	*ft_new_node(t_shell *shell, t_token *token)
{
	t_node	*list;

	list = (t_node *) ft_malloc(shell, sizeof(t_node));
	if (token)
	{
		list->content = ft_strdup(shell, token->content);
		list->type = token->type;
	}
	else
	{
		list->content = NULL;
		list->type = EMPTY_CMD;
	}
	list->next = NULL;
	list->prev = NULL;
	list->l_node = NULL;
	list->r_node = NULL;
	list->in = NULL;
	list->out = NULL;
	list->here_doc = NULL;
	list->taken = 0;
	list->here_doc = NULL;
	return (list);
}

t_node	*ft_dup_node(t_shell *shell, t_node *node)
{
	t_node	*list;

	list = (t_node *) ft_malloc(shell, sizeof(t_node));
	list->content = ft_strdup(shell, node->content);
	list->type = node->type;
	list->next = NULL;
	list->prev = NULL;
	list->in = node->in;
	list->out = node->out;
	list->here_doc = node->here_doc;
	list->l_node = NULL;
	list->r_node = NULL;
	list->taken = 0;
	return (list);
}

t_node	*ft_add_node_last(t_node **lst, t_node *new)
{
	t_node	*last;

	if (!new || !lst)
		return (NULL);
	last = ft_last_node(*lst);
	if (!last)
		return (ft_add_node_start(lst, new), new);
	last->next = new;
	new->prev = last;
	return (new);
}
