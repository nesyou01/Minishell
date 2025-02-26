#include "../../includes/minishell.h"

static char	*remove_quotes(t_shell *shell, t_token *token)
{
	t_node	*node;

	node = ft_new_node(shell, token);
	ft_remove_quotes(shell, node);
	return (node->content);
}

int	here_doc_handler(t_shell *shell, t_token *token)
{
	char	*str;
	char	*limiter;

	limiter = remove_quotes(shell, token);
	limiter = ft_expand_all_vars(shell, limiter);
	while (1)
	{
		str = readline("here_doc> ");
		if (!str)
			break ;
		ft_add_cmd_garbage(shell, str);
		str = ft_expand_all_vars(shell, str);
		if (ft_strcmp(str, limiter) == 0)
			break ;
	}
	return (0);
}
