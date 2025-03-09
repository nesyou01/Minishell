/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:07:32 by ael-gady          #+#    #+#             */
/*   Updated: 2025/03/09 23:31:13 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if(!executable)
			return (NULL);
		if (!access(executable, X_OK))
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

char	*ft_get_fullpath(t_command *p_cmd, t_shell *shell)
{
	char	*path;
	char	*env_path;
	char	**paths;

	if (!p_cmd->cmd[0])
		return (NULL);
	if (!ft_strncmp(p_cmd->cmd, "./", 2) || !ft_strncmp(p_cmd->cmd, "/", 1))
	{
		if (!access(p_cmd->cmd, X_OK))
			return (p_cmd->cmd);
		return (NULL);
	}
	env_path = get_path_from_env(shell, p_cmd->envp);
	paths = ft_split(shell, env_path, ':');
	if (!paths)
		return (NULL);
	path = get_cmd_path(shell, paths, p_cmd->cmd);
	return (path);
}
