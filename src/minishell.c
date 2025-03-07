#include "../includes/minishell.h"

void	ft_error(char *msg)//void	ft_error(t_shell *shell, char *msg)
{
	perror(msg);
	exit(1);
}

void	restore_tty(t_fd_tty *tty)
{
	if (dup2(tty->fd0, 0) == -1)
	{
		ft_error("failed to restore stdin");
		(close(tty->fd0), close(tty->fd1), close(tty->fd2));
		return ;
	}
	if (dup2(tty->fd1, 1) == -1)
	{
		ft_error("failed to restore stdout");
		(close(tty->fd0), close(tty->fd1), close(tty->fd2));
		return ;
	}
	if (dup2(tty->fd2, 2) == -1)
	{
		ft_error("failed to restore stderr");
		(close(tty->fd0), close(tty->fd1), close(tty->fd2));
		return ;
	}
}

void	execute_tree(t_shell *shell, t_node *node)
{
	if (!node)
		return;
	if (node->io && !handle_redirections(node->io))
	{
		node->exit_status = 1;
		return;
	}
	if (node->type == COMMAND)
	{
		// if (is_builtin(node->content))
		// 	execute_builtin(shell, node);
		// else
			execute_external(shell, node);
	}
	else if (node->type == PIPE)
		execute_pipe(shell, node);
	else if (node->type == AND || node->type == OR)
		execute_logical(shell, node);
	else if (node->type == SUB_SHELL)
		execute_subshell(shell, node);
	restore_tty(&shell->tty);
}

void	initialise_tty(t_fd_tty *tty)
{
	tty->fd0 = dup(0);
	if (tty->fd0 == -1)
		ft_error("failed dup");
	tty->fd1 = dup(1);
	if (tty->fd1 == -1)
		(close(tty->fd0), ft_error("failed dup"));
	tty->fd2 = dup(2);
	if (tty->fd2 == -1)
		(close(tty->fd0), close(tty->fd1), ft_error("failed dup"));
}

static void	minishell(t_shell *shell)
{
	char			*str;
	t_node			*node;

	initialise_tty(&shell->tty);
	while (!shell->exit)
	{
		str = readline("\033[32mminishell >> \033[0m");
		if (!str)
			break;
		ft_add_cmd_garbage(shell, str);
		node = ft_parser(shell, str);
		if (node)
			execute_tree(shell, node);
		restore_tty(&shell->tty);
		ft_clean_cmd(shell);
	}
	(close(shell->tty.fd0), close(shell->tty.fd1), close(shell->tty.fd2));
	ft_clean_all(shell);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void) argv;
	if (argc != 1)
		return (ft_perror("usage => ./minishell"), 1);
	env_init(&shell, env);
	shell.exit = 0;
	minishell(&shell);
	printf("%d\n", shell.tty.fd0);
	return (0);
}
