/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:18:25 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/25 20:18:20 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (!ft_strcmp(cmd, "echo"))//|| !ft_strcmp(cmd, "echo -n")
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

void	execute_builtin(t_shell *shell, t_node *node)
{
	if (ft_strcmp(node->content, "cd") == 0)
		ft_cd(shell, node);
	else if (!ft_strcmp(node->content, "echo"))// || !ft_strcmp(cmd, "echo -n")
		ft_echo(shell, node);
	else if (ft_strcmp(node->content, "export") == 0)
		ft_export(shell, node);
	else if (ft_strcmp(node->content, "unset") == 0)
		ft_unset(shell, node);
	else if (ft_strcmp(node->content, "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(node->content, "exit") == 0)
		ft_exit(shell);
}

void	hadele_redirections(t_node *node)
{
	int	fd;

	if (node->in)
	{
		fd = open(node->in->path, O_RDONLY);
		if (fd < 0)
			ft_error("failed open !");
		if (dup2(fd, STDIN_FILENO) == -1)
			(close(fd), ft_error("failed dup input !"));
		close(fd);
	}
	if (node->out)
	{
		fd = open(node->out->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			ft_error("failed open !");
		if (dup2(fd, STDOUT_FILENO) == -1)
			(close(fd), ft_error("failed dup input !"));
		close(fd);
	}
	if (node->here_doc)
	{
		//HERDOC
		//fd = open(node->here_doc->path, )
	}
}

void	execute_external(t_shell *shell, t_node *node)
{
	pid_t	pid;

	pid = fork();

	if (pid == -1)
		ft_error("failed fork !");
	if (pid == 0)
	{
		//spliting my node i think , I just realized that !
		//before pass execve, it important to check the cmd if valid or pass an path of executable !
		if (execve(node->content, node->argv, shell->env))
			ft_error("problem with execution the commande !");
	}
	//maybe handling somthing in parent process!
}
