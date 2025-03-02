/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:18:25 by ael-gady          #+#    #+#             */
/*   Updated: 2025/03/02 15:26:53 by ael-gady         ###   ########.fr       */
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

// void	execute_external(t_shell *shell, t_node *node)
// {
// 	pid_t	pid;
// 	char	*path;

// 	pid = fork();

// 	if (pid == -1)
// 		ft_error("failed fork !");
// 	if (pid == 0)
// 	{
// 		//spliting my node i think , I just realized that !
// 		//before pass execve, it important to check the cmd if valid or pass an path of executable !
// 		path = ft_get_path(shell, shell->env, node->content);
// 		printf("%s", path);
// 		if(!path)
// 			ft_error("commande not found !");
// 		char **s = malloc(2 * sizeof(char *));
// 		s[0] = ft_strdup(shell, "ls");
// 		s[1] = NULL;
// 		if (execve(path, s, NULL) == -1)//create a function of (node->argv)
// 			ft_error("problem with execution the commande !");
// 	}
// 	//maybe handling somthing in parent process!
// }


void	execute_external(t_shell *shell, t_node *node)
{
	pid_t	pid;
	int		status;
	char	*path;

	//(void)shell;
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: failed fork");
		node->exit_status = 1;
		exit(1);
	}
	else if (!pid)
	{
		path = ft_get_path(shell, shell->env, node->content);
		if (!path)
			ft_error("commande not found !");
		/*-------------*/
		node->argv = malloc(3 * sizeof(char *));
		node->argv[0] = node->content;
		// node->argv[1] = ft_strdup(shell, "-l");
		node->argv[1] = NULL;
		/*-------------*/
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