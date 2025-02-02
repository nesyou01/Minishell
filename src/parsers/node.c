#include "../../includes/minishell.h"

static int	is_redirection(t_token *token)
{
	return (token->type == OUT_REDIRECTER
			|| token->type == IN_REDIRECTER
			|| token->type == OUT_APPEND_REDIRECTER);
}

static void	set_in_or_out(t_shell *shell, t_file **in, t_file **out, t_token *token)
{
	if (token->prev->type == IN_REDIRECTER)
		*in = get_file_or_add(shell, token->content);
	else if (token->prev->type == OUT_REDIRECTER)
		*out = get_file_or_add(shell, token->content);
	else if (token->prev->type == OUT_APPEND_REDIRECTER)
		*out = get_file_or_add(shell, token->content);
}

t_node	*ft_tokens_to_nodes(t_shell *shell, t_token *token)
{
	t_node	*node;
	t_node	*tmp;
	t_file	*in;
	t_file	*out;

	in = NULL;
	out = NULL;
	node = NULL;
	while (token)
	{
		if (!is_redirection(token))
		{
			if (token->type == FILE)
				set_in_or_out(shell, &in, &out, token);
			else if (token->type == COMMAND)
			{
				tmp = ft_new_node(shell, token);
				tmp->in = in;
				tmp->out = out;
				ft_add_node_last(&node, tmp);
			}
			else
			{
				out = NULL;
				node = NULL;
				ft_add_node_last(&node, ft_new_node(shell, token));
			}
		}
		token = token->next;
	}
	return (node);
}
