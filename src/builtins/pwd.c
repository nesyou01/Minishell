/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:39:30 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/15 12:27:58 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_shell *shell, t_command *cmd)
{
	char	*path;

	(void) cmd;
	path = getcwd(NULL, 0);
	if (!path)
	{
		path = ft_get_env_value(shell, "PWD");
		printf("%s\n", path);
		return (0);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
