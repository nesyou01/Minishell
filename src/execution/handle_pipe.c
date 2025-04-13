/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:19:27 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/13 09:17:22 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	left_child(t_shell *shell, t_node *node, int *pipe_fd)
// {
// 	close(pipe_fd[0]);
// 	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
// 		(close(pipe_fd[1]), ft_error(shell, node, "failed output dup2 !", 126));
// 	close(pipe_fd[1]);
// 	execute_tree(shell, node->l_node);
// 	ft_exit(shell, node, EXIT_SUCCESS);
// }

// static void	right_child(t_shell *shell, t_node *node, int *pipe_fd)
// {
// 	close(pipe_fd[1]);
// 	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
// 		(close(pipe_fd[0]), ft_error(shell, node, "failed output dup2 !", 126));
// 	close(pipe_fd[0]);
// 	execute_tree(shell, node->r_node);
// 	ft_exit(shell, node, EXIT_SUCCESS);
// }

// void	execute_pipe(t_shell *shell, t_node *node)
// {
// 	int		pipe_fd[2];
// 	pid_t	pid_left;
// 	pid_t	pid_right;
// 	int		l_status, r_status;

// 	if (pipe(pipe_fd) == -1)
// 		ft_error(shell, node, "failed pipe !", 54);
// 	pid_left = fork();
// 	if (pid_left == -1)
// 		(close(pipe_fd[1]), close(pipe_fd[0]), ft_error(shell, node, "failed fork !", 55));
// 	if (!pid_left)
// 		left_child(shell, node, pipe_fd);
// 	pid_right = fork();
// 	if (pid_right == -1)
// 		(close(pipe_fd[1]), close(pipe_fd[0]), ft_error(shell, node, "failed fork !", 55));
// 	if (!pid_right)
// 		right_child(shell, node, pipe_fd);
// 	(close(pipe_fd[1]), close(pipe_fd[0]));
// 	(waitpid(pid_left, &l_status, 0), waitpid(pid_right, &r_status, 0));
// 	if (WIFEXITED(r_status))
// 		node->exit_status = WEXITSTATUS(r_status);
// 	else
// 		node->exit_status = 1;
// }
static void	left_child(t_shell *shell, t_node *node, int *pipe_fd)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		(close(pipe_fd[1]), ft_error(shell, node, "dup2 failed", 1));
	close(pipe_fd[1]);
	execute_tree(shell, node->l_node);
	exit_status(1, exit_status(0, 0));
	ft_exit(shell, node, exit_status(0, 0));
}

static void	right_child(t_shell *shell, t_node *node, int *pipe_fd)
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		(close(pipe_fd[0]), ft_error(shell, node, "dup2 failed", 1));
	close(pipe_fd[0]);
	execute_tree(shell, node->r_node);
	exit_status(1, exit_status(0, 0));
	ft_exit(shell, node, exit_status(0, 0));
}

void	execute_pipe(t_shell *shell, t_node *node)
{
	int		pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(pipe_fd) == -1)
		ft_error(shell, node, "pipe failed", 1);
	pid_left = fork();
	if (pid_left == -1)
		(close(pipe_fd[1]), close(pipe_fd[0]), ft_error(shell, node, "fork failed", 1));
	if (pid_left == 0)
		left_child(shell, node, pipe_fd);
	pid_right = fork();
	if (pid_right == -1)
		(close(pipe_fd[1]), close(pipe_fd[0]), ft_error(shell, node, "fork failed", 1));
	if (pid_right == 0)
		right_child(shell, node, pipe_fd);
	(close(pipe_fd[1]), close(pipe_fd[0]));
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	if (WIFEXITED(status))
		exit_status(1, WEXITSTATUS(status));
	else
		exit_status(1, 1);
}
