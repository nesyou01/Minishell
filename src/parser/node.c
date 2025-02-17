/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:08 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/17 17:05:29 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_in_or_out(t_shell *shell, t_execute *cmd, t_token *token)
{
	if (token->prev->type == IN_REDIRECTER)
		cmd->in = ft_new_file(shell, token->content);
	else if (token->prev->type == OUT_REDIRECTER)
		cmd->out = ft_new_file(shell, token->content);
	else if (token->prev->type == OUT_APPEND_REDIRECTER)
		cmd->out = ft_new_file(shell, token->content);
	else if (token->prev->type == HERE_DOC)
		cmd->here_doc = cmd->here_doc;
}

static t_node	*new_node(t_shell *shell, t_token *token, t_execute *cmd)
{
	t_node	*tmp;

	tmp = ft_new_node(shell, token);
	tmp->in = cmd->in;
	tmp->out = cmd->out;
	return (tmp);
}

static void	reset_io(t_execute *cmd)
{
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->here_doc = NULL;
}

static void	set_io_for_last_cmd(t_node *node, t_execute *cmd)
{
	while (node)
	{
		if (node->type >= 100)
			break ;
		if (node->type == COMMAND)
		{
			node->in = cmd->in;
			node->out = cmd->out;
		}
		node = node->prev;
	}
}

void	ft_tokens_to_nodes(t_shell *shell, t_token *token, t_execute *cmd)
{
	t_node	*tmp;

	tmp = NULL;
	while (token)
	{
		if (!is_redirection(token) && token->type != HERE_DOC)
		{
			if (token->type == FILE || token->type == HERE_DOC_LIMITER)
			{
				set_in_or_out(shell, cmd, token);
				set_io_for_last_cmd(tmp, cmd);
			}
			else if (token->type == COMMAND)
				tmp = ft_add_node_last(&(cmd->node),
						new_node(shell, token, cmd));
			else
			{
				reset_io(cmd);
				tmp = ft_add_node_last(&(cmd->node), ft_new_node(shell, token));
			}
			if (token->type >= 100)
				reset_io(cmd);
		}
		token = token->next;
	}
}
