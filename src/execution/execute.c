#include "../../includes/minishell.h"

int	ft_execute(t_shell *shell, t_node *node)
{
	printf("RUN --> %s\n", node->content);
	return (0);
}
