/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:18:25 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/25 16:41:28 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void exec_builtin(t_shell *shell, t_node *node)
{
	if (ft_strcmp(node->content, "cd") == 0)
		builtin_cd(node->args, shell);
	else if (ft_strcmp(node->content, "echo" || ft_strcmp(node->content, "echo -n")) == 0)
		builtin_echo(node->args);
	else if (ft_strcmp(node->content, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(node->content, "exit") == 0)
		builtin_exit(node->args, shell);
}

int	hadele_redirections(t_node *node)
{
	int	fd;

	if (node->in)
	{
		fd = open(node->in->path, O_RDONLY);
		if (fd < 0)
		{
			perror("failed open !");
			return (0);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
	}
}

void	execute_commande(t_shell *shell, t_node *node)
{
	pid_t	pid;

	if (!node->content)
		return ;
	if (is_builtins(node->content))
		return (exec_builtin(shell, node));//todo
	if (!handle_redirections(node))//todo
		return ;
	pid = fork();
	if (pid == 0)
	{
		apply_redirection(node);//for seting input && output !
		exec_cmd(shell, node);
	}
	else if (pid > 0)
	{
		// closing files or waiting ...
	}
	else
		ft_error("failed fork !");
	
}
