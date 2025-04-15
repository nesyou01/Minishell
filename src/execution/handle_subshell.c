#include "../../includes/minishell.h"

void	execute_subshell(t_shell *shell, t_node *node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		ft_error(shell, node, "failed fork !", 17);
	if (pid == 0)
	{
		if (node->io && !handle_redirections(node->io))
			ft_exit(shell, node, EXIT_FAILURE);
		execute_tree(shell, node->l_node);
		ft_exit(shell, node, exit_status(0, 0));
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exit_status(1, WEXITSTATUS(status));
		else
			exit_status(1, 1);
	}
}
