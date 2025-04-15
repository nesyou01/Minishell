/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:32:13 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/15 02:27:39 by ael-gady         ###   ########.fr       */
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

char	*get_env_value(t_shell *shell, char **envp, const char *var)
{
	size_t	len;
	int		i;

	len = ft_strlen(var);
	i = -1;
	while (envp && envp[++i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
	}
	return (NULL);
}

char	**add_to_env(t_shell *shell, char **envp, char *new_var)
{
	int		count;
	char	**new_env;

	count = 0;
	while (envp && envp[count])
		count++;
	new_env = ft_malloc(shell, sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	ft_memcpy(new_env, envp, sizeof(char *) * count);
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	free(envp);
	return (new_env);
}

static int	update_pwd_env(t_shell *shell, t_command *cmd, const char *oldpwd)
{
	char	cwd[PATH_MAX];
	int		i;
	char	*new_var;

	i = -1;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	while (cmd->envp && cmd->envp[++i])
	{
		if (ft_strncmp(cmd->envp[i], "OLDPWD=", 7) == 0)
		{
			// free(cmd->envp[i]);
			cmd->envp[i] = ft_strjoin(shell, "OLDPWD=", oldpwd);
		}
		else if (ft_strncmp(cmd->envp[i], "PWD=", 4) == 0)
		{
			// free(cmd->envp[i]);
			cmd->envp[i] = ft_strjoin(shell, "PWD=", cwd);
			return (0);
		}
	}
	new_var = ft_strjoin(shell, "PWD=", cwd);
	if (!new_var)
		return (1);
	cmd->envp = add_to_env(shell, cmd->envp, new_var);//todo
	return (0);
}

static char	*get_target_directory(t_shell *shell, t_command *cmd)
{
	char	*dir;
	char	*env_val;

	dir = cmd->argv[1];
	if (!dir || ft_strcmp(dir, "~") == 0)
	{
		env_val = get_env_value(shell, cmd->envp, "HOME");
		if (!env_val)
			ft_putstr_fd("cd: HOME not set\n", 2);
		return (env_val);
	}
	if (ft_strcmp(dir, "-") == 0)
	{
		env_val = get_env_value(shell, cmd->envp, "OLDPWD");
		if (!env_val)
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		else
		{
			ft_putstr_fd(env_val, 1);
			ft_putchar_fd('\n', 1);
		}
		return (env_val);
	}
	return (dir);
}


int	ft_cd(t_shell *shell, t_command *cmd)
{
	char	old_pwd[PATH_MAX];
	char	*target_dir;
	int		arg_count;

	arg_count = count_arguments(cmd->argv);
	if (arg_count > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		ft_memset(old_pwd, 0, sizeof(old_pwd));
	target_dir = get_target_directory(shell, cmd);
	if (!target_dir)
		return (1);
	if (chdir(target_dir) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(target_dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	return (update_pwd_env(shell, cmd, old_pwd));
}
