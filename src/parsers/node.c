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

static void	or_and_handler(t_token *token, t_node **op, t_node **cmd)
{
	int		op_type;
	t_node	*tmp;

	op_type = (*op)->type;
	if (op_type == PIPE
		|| (token->type == AND_AND && op_type == OR_OR)
		|| (token->type == OR_OR && op_type == AND_AND))
	{
		tmp = (*op)->next;
		ft_add_node_start(cmd, *op);
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

static void	ft_op_handler(t_token *token, t_node**op, t_node **cmd)
{
	if (*op)
	{
		if (token->type == OR_OR || token->type == AND_AND
			|| token->type == PIPE)
			or_and_handler(token, op, cmd);
		else if (token->type == PARENTHESES_END)
			return (par_handler(op, cmd));
	}
	ft_add_node_start(op, ft_new_node(token));
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

int	ft_node_parser(t_node **lst, t_token *token)
{
	t_node	*op;
	t_node	*cmd;

	op = NULL;
	cmd = NULL;
	while (token)
	{
		if (token->type >= 100)
			ft_op_handler(token, &op, &cmd);
		else
			ft_add_node_start(&cmd, ft_new_node(token));
		token = token->next;
	}
	move_lst(&op, &cmd);
	*lst = cmd;
	return (0);
}
