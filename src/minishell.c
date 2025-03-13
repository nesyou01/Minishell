#include "../includes/minishell.h"

void	execute_tree(t_shell *shell, t_node *node)
{
	t_command	*p_cmd;

	if (!node)
		return;
	if (node->type == COMMAND || node->type == EMPTY_CMD)
	{
		if (ft_expand_node_vars(shell, node))
			return ;
		p_cmd = ft_parse_command(shell, node); // TODO: pass it to execute_external instead of parsing again
		if (is_builtin(p_cmd))
			execute_builtin(shell, p_cmd);
		else
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

	while (1337)
	{
		str = readline("minishell $> ");
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
	signals_listener(0);
	minishell(&shell);
	return (0);
}
