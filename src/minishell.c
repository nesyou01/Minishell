/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:39:33 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/15 12:40:11 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_tree(t_shell *shell, t_node *node)
{
	t_command	*p_cmd;

	if (!node)
		return ;
	if (node->type == COMMAND || node->type == EMPTY_CMD)
	{
		if (ft_expand_node_vars(shell, node))
			return ;
		p_cmd = ft_parse_command(shell, node);
		if (p_cmd && p_cmd->cmd && is_builtin(p_cmd))
			execute_builtin(shell, node, p_cmd);
		else
			execute_external(shell, node, p_cmd);
	}
	else if (node->type == PIPE)
		execute_pipe(shell, node);
	else if (node->type == AND || node->type == OR)
		execute_logical(shell, node);
	else if (node->type == SUB_SHELL)
		execute_subshell(shell, node);
}

void	minishell(t_shell *shell)
{
	char			*str;
	t_node			*node;

	while (69)
	{
		str = readline("minishell $> ");
		if (!str)
			break ;
		signals_listener(2);
		ft_add_cmd_garbage(shell, str);
		node = ft_parser(shell, &str);
		if (node)
			execute_tree(shell, node);
		signals_listener(0);
		if (*str)
			add_history(str);
		ft_clean_cmd(shell, node);
	}
	ft_clean_all(shell, NULL);
}
