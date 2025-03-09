/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:04:14 by ael-gady          #+#    #+#             */
/*   Updated: 2025/03/09 03:57:18 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_subshell(t_shell *shell, t_node *node)
{
	pid_t	pid;
	int		status;

	if (!node || !node->l_node)
		return ;
	if (node->io && !node->l_node)
	{
		if (!handle_redirections(node->io))
			return ;//for msg error !!
		return ;
	}

	pid = fork();
	if (pid == -1)
		ft_error("failed fork !");
	if (pid == 0)
	{
		if (node->io && !handle_redirections(node->io))
			exit(1);
		execute_tree(shell, node->l_node);
		exit(node->exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		//The WIFEXITED macro checks if the child exited normally (e.g., by calling exit or returning from main).
		if (WIFEXITED(status))
			node->exit_status = WEXITSTATUS(status);// extracts the actual exit code of the child process.
		else
			node->exit_status = 1;
	}
}
