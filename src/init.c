/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:35:36 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/21 19:39:14 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	default_vars(t_shell *shell)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		ft_add_cmd_garbage(shell, path);
		ft_add_env(shell, ft_strjoin(shell, "PWD=", path));
	}
	if (!ft_get_env(shell->env, "PATH"))
		ft_add_env(shell, ft_strjoin(shell, "PATH=", DEFAULT_PATH));
}

void	env_init(t_shell *shell, char **env)
{
	t_env	*last;

	shell->env = NULL;
	shell->cmd_garbage = NULL;
	shell->globale_garbage = NULL;
	if (env && *env)
	{
		shell->env = ft_parse_env(shell, *env, NULL);
		env++;
		while (*env)
		{
			last = ft_last_env(shell->env);
			last->next = ft_parse_env(shell, *env, NULL);
			env++;
		}
	}
	default_vars(shell);
	return ;
}

int	ft_any_not_tty(void)
{
	if (!isatty(STDIN_FILENO)
		|| !isatty(STDOUT_FILENO)
		|| !isatty(STDERR_FILENO))
		return (ft_perror("In/Out not connected to a terminal"), 1);
	return (0);
}
