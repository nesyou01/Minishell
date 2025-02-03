#include "../../includes/minishell.h"

static void	set_in_or_out(t_shell *shell, t_file **in, t_file **out, t_token *token)
{
	if (token->prev->type == IN_REDIRECTER)
		*in = get_file_or_add(shell, token->content);
	else if (token->prev->type == OUT_REDIRECTER)
		*out = get_file_or_add(shell, token->content);
	else if (token->prev->type == OUT_APPEND_REDIRECTER)
		*out = get_file_or_add(shell, token->content);
}

static t_node	*new_node(t_shell *shell, t_token *token, t_file *in, t_file *out)
{
	t_node	*tmp;

	tmp = ft_new_node(shell, token);
	tmp->in = in;
	tmp->out = out;
	return (tmp);
}

static void	reset_io(t_file **in, t_file **out)
{
	*in = NULL;
	*out = NULL;
}

static void	set_io_for_last_cmd(t_node *node, t_file *in, t_file *out)
{
	while (node)
	{
		if (node->type >= 100)
			break ;
		if (node->type == COMMAND)
		{
			node->in = in;
			node->out = out;
		}
		node = node->prev;
	}
}

t_node	*ft_tokens_to_nodes(t_shell *shell, t_token *token)
{
	t_node	*node;
	t_node	*tmp;
	t_file	*in;
	t_file	*out;

	reset_io(&in, &out);
	node = NULL;
	tmp = NULL;
	while (token)
	{
		if (!is_redirection(token))
		{
			if (token->type == FILE)
			{
				set_in_or_out(shell, &in, &out, token);
				set_io_for_last_cmd(tmp, in, out);
			}
			else if (token->type == COMMAND)
			{
				tmp = new_node(shell, token, in, out);
				ft_add_node_last(&node, tmp);
			}
			else
			{
				reset_io(&in, &out);
				tmp = ft_new_node(shell, token);
				ft_add_node_last(&node, tmp);
			}
			if (token->type >= 100)
			{
				in = NULL;
				out = NULL;
			}
		}
		token = token->next;
	}
	return (node);
}
