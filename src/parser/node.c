/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:08 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/23 09:12:08 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	reset_io(t_io *io)
{
	io->here_doc = NULL;
	io->in = NULL;
	io->out = NULL;
}

static void set_io_to_node(t_node *node, t_io *io)
{
	if (!node)
		return ;
	if (node->in)
		ft_last_file(node->in)->next = io->in;
	else
		node->in = io->in;
	if (node->out)
		ft_last_file(node->out)->next = io->out;
	else
		node->out = io->out;
	if (node->here_doc)
		ft_last_file(node->here_doc)->next = io->here_doc;
	else
		node->here_doc = io->here_doc;
	reset_io(io);
}

static t_node	*new_node(t_shell *shell, t_token *token, t_io *io)
{
	t_node	*tmp;

	tmp = ft_new_node(shell, token);
	set_io_to_node(tmp, io);
	return (tmp);
}

static void	redirection_handler(t_shell *shell, t_token *token, t_io *io)
{
	char	*next;

	next = token->next->content;
	if (token->type == IN_REDIRECTER)
		ft_add_file_last(&(io->in), ft_new_file(shell, next));
	else if (token->type == OUT_REDIRECTER)
		ft_add_file_last(&(io->out), ft_new_file(shell, next));
	else
		ft_add_file_last(&(io->here_doc), ft_new_file(shell, next));
}

t_node	*ft_tokens_to_nodes(t_shell *shell, t_token *token)
{
	t_node	*head;
	t_node	*tmp;
	t_io	io;

	tmp = NULL;
	head = NULL;
	reset_io(&io);
	while (token)
	{
		if (token->type == COMMAND || token->type >= 100)
			tmp = ft_add_node_last(&head, new_node(shell, token, &io));
		else if (is_redirection(token) || token->type == HERE_DOC)
		{
			redirection_handler(shell, token, &io);
			set_io_to_node(tmp, &io);
		}
		if (token->type >= 100)
			tmp = NULL;
		token = token->next;
	}
	return (head);
}
