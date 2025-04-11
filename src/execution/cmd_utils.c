/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:07:32 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/11 20:26:29 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

static char	*check_absolute_or_relative(t_shell *shell , t_node *node, char *cmd)
{
	// Check if the command has /; If so it should be excuted if the path excutable
	if (ft_strchr(cmd, '/'))
	{
		if (is_directory(cmd))
		{
			ft_perror2(cmd, "is a directory");
			ft_exit(shell, node, 126);
		}
		// The command can be excuted
		if (!access(cmd, X_OK))
			return (cmd);
		// The command not found or cannot be excuted
		ft_perror2(cmd, "No such file or directory");
		ft_exit(shell, node, 127);
	}
	return (NULL);
}

char	*get_cmd_path(t_shell *shell, char **paths, char *cmd)
{
	char	*tmp;
	char	*executable;
	int		i;

	if (!paths || !cmd)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(shell, paths[i], "/");
		if (!tmp)
			return (NULL);
		executable = ft_strjoin(shell, tmp, cmd);
		if (!executable)
			return (NULL);
		if (!access(executable, X_OK) && !is_directory(executable))
			return (executable);
		i++;
	}
	return (NULL);
}

char	*get_path_from_env(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_strdup(shell, envp[i] + 5));
		i++;
	}
	return (NULL);
}

char	*ft_get_fullpath(t_shell *shell, t_node *node, t_command *p_cmd)
{
	char	*path;
	char	*env_path;
	char	**paths;

	if (!p_cmd->cmd[0])
		return (NULL);
	path = check_absolute_or_relative(shell, node, p_cmd->cmd);
	if (path)
		return (path);
	env_path = get_path_from_env(shell, p_cmd->envp);
	paths = ft_split(shell, env_path, ':');
	path = get_cmd_path(shell, paths, p_cmd->cmd);
	return (path);
}
