/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:35:32 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/26 11:16:31 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_tree(t_shell *shell, t_node *node)
{
	if (!node)
		return;
	if (node->in)// Handle redirections
		handle_input_redirection(node->in);
	if (node->out)
		handle_output_redirection(node->out);
	if (node->here_doc)
		handle_here_doc(node->here_doc);
	if (node->type == COMMAND)
	{
		if (is_builtin(node->content))
			execute_builtin(shell, node);
		else
			execute_external(shell, node);
	}
	else if (node->type == PIPE)
		execute_pipe(shell, node);//todo
	else if (node->type == AND || node->type == OR)
		execute_logical(shell, node);//todo
	else if (node->type == SUB_SHELL)
		execute_subshell(shell, node);//todo
}

static void	minishell(t_shell *shell)
{
	char			*str;
	t_node			*node;

	while (!shell->exit)
	{
		str = readline("\033[32mminishell >> \033[0m");
		if (!str)
			break ;
		ft_add_garbage(&(shell->cmd_garbage), shell, str);
		node = ft_parser(shell, str);
		if (node)
			execute_tree(shell, node);//todo->
		ft_clean_cmd(shell);
	}
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
	return (0);
}
