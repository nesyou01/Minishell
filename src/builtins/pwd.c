/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:39:30 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/22 01:08:21 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*_pwd(t_shell *shell, int flag, char *new)
{
	char		*tmp;
	static char	*pwd = NULL;

	if (flag == 1 || flag == 2)
	{
		if (new)
			tmp = ft_strdup_globale(shell, new);
		else
		{
			tmp = getcwd(NULL, 0);
			if (tmp)
				ft_add_globale_garbage(shell, tmp);
		}
		if (tmp)
		{
			pwd = tmp;
			ft_add_env(shell, ft_strjoin(shell, "PWD=", pwd));
		}
	}
	if (flag == 2)
		return (tmp);
	return (pwd);
}

int	ft_pwd(t_shell *shell, t_command *cmd)
{
	char	*path;

	(void) cmd;
	path = _pwd(shell, 1, NULL);
	printf("%s\n", path);
	return (0);
}
