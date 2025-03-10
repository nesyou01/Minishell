/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:08 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/10 04:31:25 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void set_io_to_node(t_node *node, t_file **io)
{
	if (!node)
		return ;
	if (node->io)
		ft_last_file(node->io)->next = *io;
	else
		node->io = *io;
	*io = NULL;
}

static t_node	*new_node(t_shell *shell, t_token *token, t_file **io)
{
	t_node	*tmp;

	tmp = ft_new_node(shell, token);
	set_io_to_node(tmp, io);
	return (tmp);
}

static int	redirection_handler(t_shell *shell, t_token *token, t_file **io)
{
	t_node	*next;
	t_list	*lst;
	t_file	*file;

	next = ft_new_node(shell, token->next);
	if (ft_expand_node_vars(shell, next))
		return (1);
	lst = ft_split_node(shell, next);
	file = ft_new_file(shell, token->next);
	file->path = next->content;
	file->type = token->type;
	file->is_ambiguous = !next || lst->next;
	ft_add_file_last(io, file);
	return (0);
}

static void	add_empty_node(t_node **head, t_shell *shell, t_file **io)
{
	t_node	*node;

	node = new_node(shell,
			ft_new_token(shell, ft_strdup(shell, "")), io);
	node->type = EMPTY_CMD;
	ft_add_node_last(head, node);
}

t_node	*ft_tokens_to_nodes(t_shell *shell, t_token *token)
{
	t_node	*head;
	t_node	*tmp;
	t_file	*io;

	tmp = NULL;
	io = NULL;
	head = NULL;
	while (token)
	{
		if (token->type == COMMAND || token->type >= 100)
			tmp = ft_add_node_last(&head, new_node(shell, token, &io));
		else if (is_redirection(token))
		{
			if (redirection_handler(shell, token, &io))
				return (NULL);
			set_io_to_node(tmp, &io);
		}
		if((!token->next || token->next->type >= 100) && !tmp)
			add_empty_node(&head, shell, &io);
		if (token->type >= 100 && token->type != PARENTHESES_END)
			tmp = NULL;
		token = token->next;
	}
	return (head);
}
