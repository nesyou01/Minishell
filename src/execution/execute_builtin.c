/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:51:51 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/20 02:58:14 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_command *p_cmd)
{
	if (!p_cmd)
		return (0);
	return (!ft_strcmp2(p_cmd->cmd, "cd")
		|| !ft_strcmp2(p_cmd->cmd, "echo")
		|| !ft_strcmp2(p_cmd->cmd, "export")
		|| !ft_strcmp2(p_cmd->cmd, "unset")
		|| !ft_strcmp2(p_cmd->cmd, "env")
		|| !ft_strcmp2(p_cmd->cmd, "exit")
		|| !ft_strcmp2(p_cmd->cmd, "pwd"));
}

static void	set_error(void)
{
	exit_status(1, 1);
}

static void	save_tty(t_shell *shell, t_node *node, int *fds)
{
	fds[0] = dup(0);
	if (fds[0] == -1)
		ft_error(shell, node, "failed dup", 1);
	fds[1] = dup(1);
	if (fds[1] == -1)
	{
		close(fds[0]);
		ft_error(shell, node, "failed dup", 1);
	}
	fds[2] = dup(2);
	if (fds[2] == -1)
	{
		(close(fds[0]), close(fds[1]));
		ft_error(shell, node, "failed dup", 1);
	}
}

static void	reset_tty(t_shell *shell, t_node *node, int *fd)
{
	if (dup2(fd[0], 0) == -1)
	{
		(close(fd[0]), close(fd[1]), close(fd[2]));
		ft_error(shell, node, "failed dup", 1);
	}
	if (dup2(fd[1], 1) == -1)
	{
		(close(fd[0]), close(fd[1]), close(fd[2]));
		ft_error(shell, node, "failed dup", 1);
	}
	if (dup2(fd[2], 2) == -1)
	{
		(close(fd[0]), close(fd[1]), close(fd[2]));
		ft_error(shell, node, "failed dup", 1);
	}
}

void	execute_builtin(t_shell *shell, t_node *node, t_command *p_cmd)
{
	int	fds[3];
	int	status;

	if (!handle_redirections(shell, node->io))
		return (set_error());
	save_tty(shell, node, fds);
	if (!ft_strcmp2(p_cmd->argv[0], "cd"))
		status = ft_cd(shell, p_cmd);
	else if (!ft_strcmp2(p_cmd->argv[0], "echo"))
		status = ft_echo(p_cmd);
	else if (!ft_strcmp2(p_cmd->argv[0], "export"))
		status = ft_export(shell, p_cmd);
	else if (!ft_strcmp2(p_cmd->argv[0], "unset"))
		status = ft_unset(shell, p_cmd);
	else if (!ft_strcmp2(p_cmd->argv[0], "env"))
		status = ft_env(shell, p_cmd);
	else if (!ft_strcmp2(p_cmd->argv[0], "pwd"))
		status = ft_pwd(shell, p_cmd);
	else
		status = ft_builtin_exit(shell, node, p_cmd, fds);
	reset_tty(shell, node, fds);
	exit_status(1, status);
	(close(fds[0]), close(fds[1]), close(fds[2]));
}
