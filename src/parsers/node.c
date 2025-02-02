#include "../../includes/minishell.h"

t_node	*ft_tokens_to_nodes(t_shell *shell, t_token *token)
{
	t_node	*node;

	node = NULL;
	while (token)
	{
		printf("%s\n", token->content);
		ft_add_node_last(&node, ft_new_node(shell, token));
		token = token->next;
	}
	return (node);
}
