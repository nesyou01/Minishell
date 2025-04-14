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

static void	convert_here_doc(t_token *token)
{
	token->prev->type = IN_REDIRECTER;
	token->type = FILE;
}

static void	read_here_doc(t_shell *shell, char *limiter, int has_quote, int fds[2])
{
	char	*str;

	close(fds[0]);
	signals_listener(1);
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
	close(fds[1]);
	ft_exit(shell, NULL, EXIT_SUCCESS);
}

int	here_doc_handler(t_shell *shell, t_token *token)
{
	char	*limiter;
	int		fds[2];
	int		has_quote;
	pid_t	pid;
	int		status;

	if (ft_pipe(fds))
		return (1);
	has_quote = ft_strchr(token->content, '\'') || ft_strchr(token->content, '"');
	convert_here_doc(token);
	token->fd = fds[0];
	limiter = remove_quotes(shell, token);
	pid = fork();
	if (pid == -1)
		return (close(fds[1]), close(fds[0]), 1);
	if (pid == 0)
		read_here_doc(shell, limiter, has_quote, fds);
	close(fds[1]);
	waitpid(pid, &status, 0);
	status = WEXITSTATUS(status);
	if (status)
		close(fds[0]);
	return (status);
}
