/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:32:13 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/22 01:13:48 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	update_pwd_env(t_shell *shell, t_command *cmd, const char *oldpwd)
{
	char	*cwd;

	cwd = _pwd(shell, 2, NULL);
	if (!cwd)
	{
		ft_perror3("cd", "error retrieving current directory", strerror(errno));
		if (ft_strcmp(cmd->argv[1], "..") || ft_strcmp(cmd->argv[1], "."))
			_pwd(shell, 1, ft_strjoin(shell, "PWD=",
					ft_strjoin(shell, _pwd(shell, 0, NULL),
						ft_strjoin(shell, "/", cmd->argv[1]))));
		return (1);
	}
	ft_add_env(shell, ft_strjoin(shell, "OLDPWD=", oldpwd));
	return (0);
}

int	ft_cd(t_shell *shell, t_command *cmd)
{
	char	*old_pwd;
	char	*target_dir;

	target_dir = cmd->argv[1];
	if (!target_dir)
		return (ft_perror2("cd", "with only a relative or absolute path"), 1);
	old_pwd = _pwd(shell, 1, NULL);
	if (chdir(target_dir) == -1)
		return (ft_perror3("cd", target_dir, strerror(errno)), 1);
	return (update_pwd_env(shell, cmd, old_pwd));
}
