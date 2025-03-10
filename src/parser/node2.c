/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:56 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/10 20:56:28 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	or_and_handler(t_shell *shell,
	t_node *node, t_node **op, t_node **cmd)
{
	int		op_type;
	t_node	*tmp;

	op_type = (*op)->type;
	if (op_type == PIPE
		|| (node->type == AND && op_type == OR)
		|| (node->type == OR && op_type == AND))
	{
		tmp = (*op)->next;
		ft_add_node_start(cmd, ft_dup_node(shell, *op));
		*op = tmp;
	}
}

static void	par_end_handler(t_shell *shell, t_node **op, t_node **cmd, t_node *node)
{
	t_node	*tmp;

	while ((*op)->type != PARENTHESES_START)
	{
		tmp = (*op)->next;
		ft_add_node_start(cmd, *op);
		*op = tmp;
	}
	tmp = ft_dup_node(shell, node);
	tmp->type = SUB_SHELL;
	ft_add_node_start(cmd, tmp);
	*op = (*op)->next;
}

static void	ft_op_handler(t_shell *shell,
	t_node *node, t_node**op, t_node **cmd)
{
	if (*op)
	{
		if (node->type == OR || node->type == AND
			|| node->type == PIPE)
			or_and_handler(shell, node, op, cmd);
		else if (node->type == PARENTHESES_END)
			return (par_end_handler(shell, op, cmd, node));
	}
	ft_add_node_start(op, ft_dup_node(shell, node));
}

static void	move_lst(t_node **a, t_node **b)
{
	t_node	*tmp;

	while (*a)
	{
		tmp = (*a)->next;
		(*a)->prev = NULL;
		ft_add_node_start(b, *a);
		*a = tmp;
	}
}

void	ft_tree_builder(t_shell *shell, t_node **node)
{
	t_node	*op;
	t_node	*cmd;
	t_node	*tmp;

	op = NULL;
	cmd = NULL;
	tmp = *node;
	while (tmp)
	{
		if (tmp->type >= 100)
			ft_op_handler(shell, tmp, &op, &cmd);
		else
			ft_add_node_start(&cmd, ft_dup_node(shell, tmp));
		tmp = tmp->next;
	}
	move_lst(&op, &cmd);
	*node = cmd;
	ft_to_tree(cmd);
}

t_node	*ft_head_node(t_node *node)
{
	if (!node)
		return (NULL);
	while (node->prev)
		node = node->prev;
	return (node);
}
