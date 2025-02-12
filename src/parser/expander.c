#include "../../includes/minishell.h"


void	ft_expander(t_shell *shell, t_node *node)
{
	while (node)
	{
		ft_expand_quotes(shell, node);
		node = node->next;
	}
}
