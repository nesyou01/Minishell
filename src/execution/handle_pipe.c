/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:19:27 by ael-gady          #+#    #+#             */
/*   Updated: 2025/03/01 10:42:02 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	left_child(t_shell *shell, t_node *node, int *pipe_fd)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		(close(pipe_fd[1]), ft_error("failed output dup2 !"));
	close(pipe_fd[1]);
	execute_tree(shell, node->l_node);
	//exit(EXIT_SUCCESS);//the child processes after calling execute_tree is a safety measure
	exit(node->exit_status);
}

static void	right_child(t_shell *shell, t_node *node, int *pipe_fd)
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		(close(pipe_fd[0]), ft_error("failed output dup2 !"));
	close(pipe_fd[0]);
	execute_tree(shell, node->r_node);
	//exit(EXIT_SUCCESS);
	exit(node->exit_status);
}

void	execute_pipe(t_shell *shell, t_node *node)
{
	int	pipe_fd[2];
	int	pid_left;
	int	pid_right;

	if (pipe(pipe_fd) == -1)
		ft_error("failed pipe !");
	pid_left = fork();
	if (pid_left == -1)
		(close(pipe_fd[1]), close(pipe_fd[0]), ft_error("failed fork !"));
	if (!pid_left)
		left_child(shell, node, pipe_fd);
	pid_right = fork();
	if (pid_left == -1)
		(close(pipe_fd[1]), close(pipe_fd[0]), ft_error("failed fork !"));
	if (pid_right)
		right_child(shell, node, pipe_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, NULL, 0);
}
