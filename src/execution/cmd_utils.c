/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:07:32 by ael-gady          #+#    #+#             */
/*   Updated: 2025/03/11 04:43:21 by ael-gady         ###   ########.fr       */
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

static char	*check_absolute_or_relative(char *cmd)
{
	if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, "..") || !ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
	{
		if (is_directory(cmd))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": is a directory\n", 2);
			return (NULL);//ft_exit(shell, node, 126);
		}
		if (!access(cmd, X_OK | F_OK))
			return (cmd);
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

char	*ft_get_fullpath(t_command *p_cmd, t_shell *shell)
{
	char	*path;
	char	*env_path;
	char	**paths;

	if (!p_cmd->cmd[0])
		return (NULL);
	path = check_absolute_or_relative(p_cmd->cmd);
	if (path)
		return (path);
	env_path = get_path_from_env(shell, p_cmd->envp);
	paths = ft_split(shell, env_path, ':');
	path = get_cmd_path(shell, paths, p_cmd->cmd);
	return (path);
}
