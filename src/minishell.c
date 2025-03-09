#include "../includes/minishell.h"

void	execute_tree(t_shell *shell, t_node *node)
{
	if (!node)
		return;
	if (node->type == COMMAND || node->type == EMPTY_CMD)
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
}

static void	minishell(t_shell *shell)
{
	char			*str;
	t_node			*node;

	while (!shell->exit)
	{
		str = readline("\033[32mminishell >> \033[0m");
		if (!str)
			break;
		ft_add_cmd_garbage(shell, str);
		node = ft_parser(shell, &str);
		if (node)
			execute_tree(shell, node);
		if (*str)
			add_history(str);
		ft_clean_cmd(shell, node);
	}
	ft_clean_all(shell, NULL);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void) argv;
	if (argc != 1)
		return (ft_perror("usage => ./minishell"), 1);
	env_init(&shell, env);
	shell.exit = 0;
	signals_listener(&shell);
	minishell(&shell);
	return (0);
}
