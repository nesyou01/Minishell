/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:50:50 by ylagmah           #+#    #+#             */
/*   Updated: 2025/01/30 14:56:13 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	or_and_handler(t_shell *shell, t_node *node, t_node **op, t_node **cmd)
{
	int		op_type;
	t_node	*tmp;

	op_type = (*op)->type;
	if (op_type == PIPE
		|| (node->type == AND_AND && op_type == OR_OR)
		|| (node->type == OR_OR && op_type == AND_AND))
	{
		tmp = (*op)->next;
		ft_add_node_start(cmd, ft_dup_node(shell, *op));
		*op = tmp;
	}
}

static void	par_handler(t_node **op, t_node **cmd)
{
	t_node	*tmp;

	while ((*op)->type != PARENTHESES_START)
	{
		tmp = (*op)->next;
		ft_add_node_start(cmd, *op);
		*op = tmp;
	}
	tmp = (*op)->next;
	free((*op)->content);
	free(*op);
	*op = tmp;
}

static void	ft_op_handler(t_shell *shell, t_node *node, t_node**op, t_node **cmd)
{
	if (*op)
	{
		if (node->type == OR_OR || node->type == AND_AND
			|| node->type == PIPE)
			or_and_handler(shell, node, op, cmd);
		else if (node->type == PARENTHESES_END)
			return (par_handler(op, cmd));
	}
	ft_add_node_start(op, ft_dup_node(shell, node));
}

static void	move_lst(t_node **a, t_node **b)
{
	t_node	*tmp;

	while (*a)
	{
		tmp = (*a)->next;
		ft_add_node_start(b, *a);
		*a = tmp;
	}
}

void	ft_node_parser(t_shell *shell, t_node **node)
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
}
