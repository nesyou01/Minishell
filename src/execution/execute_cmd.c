/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:18:25 by ael-gady          #+#    #+#             */
/*   Updated: 2025/03/09 20:36:28 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

// void	execute_builtin(t_shell *shell, t_node *node)
// {
// 	if (ft_strcmp(node->content, "cd") == 0)
// 		ft_cd(shell, node); 
// 	else if (!ft_strcmp(node->content, "echo"))
// 		ft_echo(shell, node);
// 	else if (ft_strcmp(node->content, "export") == 0)
// 		ft_export(shell, node);
// 	else if (ft_strcmp(node->content, "unset") == 0)
// 		ft_unset(shell, node);
// 	else if (ft_strcmp(node->content, "env") == 0)
// 		ft_env(shell);
// 	else if (ft_strcmp(node->content, "exit") == 0)
// 		ft_exit(shell);
// }

void	exec_child(t_shell *shell, t_node *node)
{
	t_command	*p_cmd;
	char		*path;

	if (node->io && !handle_redirections(node->io))
		exit(1);
	p_cmd = ft_parse_command(shell, node);
	if (!p_cmd || !p_cmd->argv[0])
		exit(0);
	path = ft_get_fullpath(p_cmd, shell);
	if (!path)
	{
		ft_perror("command not found!");
		exit(127);
	}
	if (execve(path, p_cmd->argv, p_cmd->envp) == -1)
	{
		ft_perror("minishell: execve failed");
		free(path);
		exit(127);
	}
}

void	execute_external(t_shell *shell, t_node *node)
{
	pid_t	pid;
	int		status;

	ft_expand_node_vars(shell, node);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: failed fork");
		node->exit_status = 1;
		exit(1);
	}
	if (!pid)
		exec_child(shell, node);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("minishell: failed waitpid");
			node->exit_status = 1;
			return ;
		}
		if (WIFEXITED(status))
			node->exit_status = WEXITSTATUS(status);
		else
			node->exit_status = 1;
	}
}

