/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:04:14 by ael-gady          #+#    #+#             */
/*   Updated: 2025/03/10 00:13:43 by ylagmah          ###   ########.fr       */
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
		ft_error(shell, node, "failed fork !", 17);
	if (pid == 0)
	{
		if (node->io && !handle_redirections(node->io))
			ft_exit(shell, node, EXIT_FAILURE);
		execute_tree(shell, node->l_node);
		ft_exit(shell, node, node->exit_status);
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
