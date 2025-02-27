/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:04:14 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/27 16:50:59 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_subshell(t_shell *shell, t_node *node)
{
	pid_t	pid;
	int		status;

	if (!node || !node->l_node || !node->r_node)
		return ;
	pid = fork();
	if (pid == -1)
		ft_error("failed fork !");
	if (pid == 0)
	{
		execute_tree(shell, node->l_node);
		exit(node->exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			node->exit_status = WEXITSTATUS(status);
		else
			node->exit_status = 1;
	}
}
