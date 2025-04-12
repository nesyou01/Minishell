/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:32:13 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/11 20:41:24 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_shell *shell, t_command *parse_cmd)
{
	char	*dir;

	(void) shell;
	dir = parse_cmd->argv[1];
	if (!dir || ft_strcmp(dir, "~"))
		dir = getenv("HOME");
	if(chdir(dir) == -1)
	{
		perror("failed chdir ! ");
		return (1);
	}
	return (0);
}
