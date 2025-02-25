/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:35:32 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/25 14:12:09 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_tree(t_shell *shell, t_node *node)
{
	if (!node)
		return ;
	if (node->type == COMMAND)
		execute_commande(shell, node);
	else if (node->type == PIPE)
		execute_pipe(shell , node);
	else if (node->type == AND)
		execute_and(shell, node);
	else if (node->type == OR)
		execute_or(shell, node);
	else if (node->type == SUB_SHELL)
		execute_subshell(shell, node);
	// else if (node->type == OUT_REDIRECTER || node->type == IN_REDIRECTER ||
	// 		 node->type == OUT_APPEND_REDIRECTER || node->type == HERE_DOC)
	// 	execute_redirection(shell, node);
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
