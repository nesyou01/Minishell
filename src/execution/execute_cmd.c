/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:18:25 by ael-gady          #+#    #+#             */
/*   Updated: 2025/03/08 00:01:11 by ylagmah          ###   ########.fr       */
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

/* I should handle the cases of tr ' ' '\n' and  echo "hello world" */
void	execute_external(t_shell *shell, t_node *node)
{
	pid_t	pid;
	int		status;
	char	*path;

	ft_expand_node_vars(shell, node);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: failed fork");
		node->exit_status = 1;
		exit(1);
	}
	else if (!pid)
	{
		if (!node->content)
			exit(0);
		node->argv = ft_split_(node->content, ' ');
		if (!node->argv || !node->argv[0])
			ft_error("commande not found !");
		path = ft_get_path(shell, shell->env, node->argv[0]);
		if (!path)
			ft_error("commande not found !");
		if (execve(path, node->argv, shell->envp) == -1)
		{
			perror("minishell: execve, commande not found !");
			free(path);
			exit(1);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("minishell: waitpid");
			node->exit_status = 1;
			return;
		}
		if (WIFEXITED(status))
			node->exit_status = WEXITSTATUS(status);
		else
			node->exit_status = 1;
	}
}
