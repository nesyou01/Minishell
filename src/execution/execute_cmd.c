/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:51:15 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/20 03:29:55 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_command(t_shell *shell, t_node *node, char *path,
						t_command *p_cmd)
{
	if (!path)
		ft_exit(shell, node, 127);
	if (execve(path, p_cmd->argv, p_cmd->envp) == -1)
	{
		ft_perror2(path, strerror(errno));
		if (errno == ENOENT)
            ft_exit(shell, node, 127);
        else if (errno == EACCES)
            ft_exit(shell, node, 126);
        else
            ft_exit(shell, node, 1);
	}
}

void	exec_child(t_shell *shell, t_node *node, t_command *p_cmd)
{
	char		*path;

	if (node->io && !handle_redirections(shell, node->io))
		ft_exit(shell, node, EXIT_FAILURE);
	if (!p_cmd || !p_cmd->argv[0])
		ft_exit(shell, node, EXIT_SUCCESS);
	path = ft_get_fullpath(shell, node, p_cmd);
	if (!path)
	{
		ft_perror2(p_cmd->cmd, "command not found");
		ft_exit(shell, node, 127);
	}
	signals_listener(3);
	exec_command(shell, node, path, p_cmd);
}

static void	sig_exit(int status)
{
	int		sig;

	sig = WTERMSIG(status);
	if (sig >= 3)
		printf("Quit: %d", sig);
	printf("\n");
	exit_status(1, 128 + sig);
}

void	execute_external(t_shell *shell, t_node *node, t_command *p_cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_perror("failed fork");
		exit_status(1, 1);
		ft_exit(shell, node, EXIT_FAILURE);
	}
	if (!pid)
		exec_child(shell, node, p_cmd);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			return (exit_status(1, 1), ft_perror("failed waitpid"));
		if (WIFEXITED(status))
			exit_status(1, WEXITSTATUS(status));
		else
			sig_exit(status);
	}
}
