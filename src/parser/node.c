/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:08 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/21 14:30:42 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void set_io_to_node(t_node *node, t_execute *ex)
{
	if (!node)
		return ;
	if (node->in)
		ft_last_file(node->in)->next = ex->in;
	else
		node->in = ex->in;
	if (node->out)
		ft_last_file(node->out)->next = ex->out;
	else
		node->out = ex->out;
	if (node->here_doc)
		ft_last_file(node->here_doc)->next = ex->here_doc;
	else
		node->here_doc = ex->here_doc;
	ex->in = NULL;
	ex->out = NULL;
	ex->here_doc = NULL;
}

static t_node	*new_node(t_shell *shell, t_token *token, t_execute *ex)
{
	t_node	*tmp;

	tmp = ft_new_node(shell, token);
	set_io_to_node(tmp, ex);
	return (tmp);
}

static void	redirection_handler(t_shell *shell, t_token *token, t_execute *ex)
{
	char	*next;

	next = token->next->content;
	if (token->type == IN_REDIRECTER)
		ft_add_file_last(&(ex->in), ft_new_file(shell, next));
	else if (token->type == OUT_REDIRECTER)
		ft_add_file_last(&(ex->out), ft_new_file(shell, next));
	else
		ft_add_file_last(&(ex->here_doc), ft_new_file(shell, next));
}

void	ft_tokens_to_nodes(t_shell *shell, t_token *token, t_execute *ex)
{
	t_node	*tmp;

	tmp = NULL;
	while (token)
	{
		if (token->type == COMMAND || token->type >= 100)
			tmp = ft_add_node_last(&(ex->node), new_node(shell, token, ex));
		else if (is_redirection(token) || token->type == HERE_DOC)
		{
			redirection_handler(shell, token, ex);
			set_io_to_node(tmp, ex);
		}
		if (token->type >= 100)
			tmp = NULL;
		token = token->next;
	}
}
