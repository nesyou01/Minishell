/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:04:14 by ael-gady          #+#    #+#             */
/*   Updated: 2025/03/03 17:51:07 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		//The WIFEXITED macro checks if the child exited normally (e.g., by calling exit or returning from main).
		if (WIFEXITED(status))
			node->exit_status = WEXITSTATUS(status);// extracts the actual exit code of the child process.
		else
			node->exit_status = 1;
	}
}
