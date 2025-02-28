#include "../../includes/minishell.h"

static char	*remove_quotes(t_shell *shell, t_token *token)
{
	t_node	*node;

	node = ft_new_node(shell, token);
	ft_remove_quotes(shell, node);
	return (ft_expand_all_vars(shell, node->content));
}

static int	ft_pipe(int fds[2])
{
	fds[1] = open("/tmp/.heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fds[1] == -1)
		return (1);
	fds[0] = open("/tmp/.heredoc_tmp", O_RDONLY);
	if (fds[0] == -1)
		return (close(fds[1]), 1);
	unlink("/tmp/.heredoc_tmp");
	return (0);
}

int	here_doc_handler(t_shell *shell, t_token *token)
{
	char	*str;
	char	*limiter;
	int		fds[2];
	int		has_quote;

	if (ft_pipe(fds))
		return (1);
	has_quote = ft_strchr(token->content, '\'') || ft_strchr(token->content, '"');
	token->prev->type = IN_REDIRECTER;
	token->prev->fd = fds[0];
	limiter = remove_quotes(shell, token);
	while (1)
	{
		str = readline("here_doc> ");
		if (!str)
			break ;
		ft_add_cmd_garbage(shell, str);
		if (!has_quote)
			str = ft_expand_all_vars(shell, str);
		if (ft_strcmp(str, limiter) == 0)
			break ;
		ft_putstr_fd(str, fds[1]);
		ft_putstr_fd("\n", fds[1]);
	}
	return (0);
}
