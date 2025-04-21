/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:07:32 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/21 19:33:13 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*check_absolute_or_relative(t_shell *shell,
	t_node *node, char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (is_directory(cmd))
		{
			ft_perror2(cmd, "is a directory");
			ft_exit(shell, node, 126);
		}
		if (!access(cmd, F_OK))
			return (cmd);
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
		if (!access(executable, F_OK) && !is_directory(executable))
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

static char	*get_executable_from_cwd(t_shell *shell, t_command *p_cmd)
{
	char	*cwd;
	char	*tmp;
	char	*fullpath;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	ft_add_cmd_garbage(shell, cwd);
	tmp = ft_strjoin(shell, cwd, "/");
	fullpath = ft_strjoin(shell, tmp, p_cmd->cmd);
	if (!access(fullpath, F_OK) && !is_directory(fullpath))
		return (fullpath);
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
	if (!env_path || !*env_path)
		return (get_executable_from_cwd(shell, p_cmd));
	paths = ft_split(shell, env_path, ':');
	path = get_cmd_path(shell, paths, p_cmd->cmd);
	return (path);
}
