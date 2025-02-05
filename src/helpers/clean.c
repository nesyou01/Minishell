#include "../../includes/minishell.h"

static void	clear_garbage(t_list *garbage)
{
	t_list	*tmp;

	while (garbage)
	{
		tmp = garbage->next;
		free(garbage->content);
		free(garbage);
		garbage = tmp;
	}
}

void	ft_clean_all(t_shell *shell)
{
	// TODO: close fds
	if (shell->garbage)
		clear_garbage(shell->garbage);
	shell->garbage = NULL;
}
