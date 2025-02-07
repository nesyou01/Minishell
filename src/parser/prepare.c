#include "../../includes/minishell.h"

void	ft_prepare_cmd(t_shell *shell, t_node *node)
{
	char	*op;

	if (!node)
		return ;
	if (node->type >= 100)
	{
		printf("%s\n", node->content);
		ft_prepare_cmd(shell, node->l_node);
		ft_prepare_cmd(shell, node->r_node);
		return ;
	}
	ft_execute(shell, node);
}
