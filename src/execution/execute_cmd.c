/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:18:25 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/12 15:33:35 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_command *p_cmd)
{
	if (!p_cmd)
		return (0);
	if (!ft_strcmp2(p_cmd->cmd, "cd"))
		return (1);
	if (!ft_strcmp2(p_cmd->cmd, "echo"))
		return (1);
	if (!ft_strcmp2(p_cmd->cmd, "export"))
		return (1);
	if (!ft_strcmp2(p_cmd->cmd, "unset"))
		return (1);
	if (!ft_strcmp2(p_cmd->cmd, "env"))
		return (1);
	if (!ft_strcmp2(p_cmd->cmd, "exit"))
		return (1);
	return (0);
}

void	execute_builtin(t_shell *shell, t_node *node, t_command *p_cmd)
{
	if (!ft_strcmp2(p_cmd->argv[0], "cd"))
		ft_cd(shell, p_cmd);
	else if (!ft_strcmp2(p_cmd->argv[0], "echo"))
		ft_echo(shell, p_cmd);//done
	else if (!ft_strcmp2(p_cmd->argv[0], "export"))
		ft_export(shell, p_cmd);//done
	else if (!ft_strcmp2(p_cmd->argv[0], "unset"))
		ft_unset(shell, p_cmd);//done
	else if (!ft_strcmp2(p_cmd->argv[0], "env"))
		ft_env(shell);//done
	else if (!ft_strcmp2(p_cmd->argv[0], "pwd"))
		ft_pwd(shell, p_cmd);//todo
	else if (!ft_strcmp2(p_cmd->argv[0], "exit"))
		ft_builtin_exit(shell, node, p_cmd);
}

static void	handle_dot_command(t_shell *shell, t_node *node, t_command *p_cmd)
{
	if (!ft_strcmp(p_cmd->cmd, "."))
	{
		if (!p_cmd->argv[1])
		{
			ft_putstr_fd("minishell: .: filename argument required\n", 2);
			ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
			ft_exit(shell, node, 2);
		}
		ft_exit(shell, node, EXIT_SUCCESS);
	}
}

static void	double_dot_cmd(t_shell *shell, t_node *node, t_command *p_cmd)
{
	if (!ft_strcmp(p_cmd->cmd, ".."))
	{
		ft_putstr_fd("minishell: ..: command not found\n", 2);
		ft_exit(shell, node, 127);
	}
}

static void	exec_command(t_shell *shell, t_node *node, char *path,
						t_command *p_cmd)
{
	if (!path)
		ft_exit(shell, node, 127);
	if (execve(path, p_cmd->argv, p_cmd->envp) == -1)
	{
		ft_perror("minishell: execve failed");
		ft_exit(shell, node, 127);
	}
}

void	exec_child(t_shell *shell, t_node *node)
{
	t_command	*p_cmd;
	char		*path;

	if (node->io && !handle_redirections(node->io))
		ft_exit(shell, node, EXIT_FAILURE);
	p_cmd = ft_parse_command(shell, node);
	if (!p_cmd || !p_cmd->argv[0])
		ft_exit(shell, node, EXIT_SUCCESS);
	handle_dot_command(shell, node, p_cmd);
	double_dot_cmd(shell, node, p_cmd);
	path = ft_get_fullpath(shell, node, p_cmd);
	if (!path)
	{
		ft_perror("command not found!");
		ft_exit(shell, node, 127);
	}
	exec_command(shell, node, path, p_cmd);
}

void	execute_external(t_shell *shell, t_node *node, t_command *p_cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: failed fork");
		exit_status(1, 1);
		ft_exit(shell, node, EXIT_FAILURE);
	}
	if (!pid)
		exec_child(shell, node);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("minishell: failed waitpid");
			exit_status(1, 1);
			return ;
		}
		if (WIFEXITED(status))
			exit_status(1, WEXITSTATUS(status));
		else
			exit_status(1, 1);
	}
}

