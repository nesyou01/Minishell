/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:32:13 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/17 12:02:02 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_arguments(char **argv)
{
	int	count;

	count = 0;
	if (!argv)
		return (0);
	while (argv[count])
		count++;
	return (count);
}

static int	update_pwd_env(t_shell *shell, t_command *cmd, const char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_perror3("cd", "error retrieving current directory", strerror(errno));
		if (ft_strcmp(cmd->argv[1], "..") || ft_strcmp(cmd->argv[1], "."))
		{
			ft_add_env(shell, ft_strjoin(shell, "PWD+=/", cmd->argv[1]));
		}
		return (1);
	}
	ft_add_env(shell, ft_strjoin(shell, "OLDPWD=", oldpwd));
	ft_add_env(shell, ft_strjoin(shell, "PWD=", cwd));
	return (0);
}

int	ft_cd(t_shell *shell, t_command *cmd)
{
	char	old_pwd[PATH_MAX];
	char	*target_dir;
	int		arg_count;

	arg_count = count_arguments(cmd->argv);
	if (arg_count > 2)
		return (ft_perror2("cd", "too many arguments"), 1);
	target_dir = cmd->argv[1];
	if (!target_dir)
		return (ft_perror2("cd", "with only a relative or absolute path"), 1);
	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		ft_memset(old_pwd, 0, sizeof(old_pwd));
	if (chdir(target_dir) == -1)
		return (ft_perror3("cd", target_dir, strerror(errno)), 1);
	return (update_pwd_env(shell, cmd, old_pwd));
}
