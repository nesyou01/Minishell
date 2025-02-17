/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:33:36 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/17 11:03:54 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*read_dir(t_shell *shell, DIR *dir)
{
	char			*str;
 	struct dirent	*dr;

	str = NULL;
 	while (1)
	{
		dr = readdir(dir);
		if (!dr)
			break ;
		if (dr->d_name[0] != '.')
		{
			if (str)
				str = ft_strjoin(shell, str, " ");
			str = ft_strjoin(shell, str, dr->d_name);
		}
	}
	return (str);
}

int	ft_expand_wildcards(t_shell *shell, t_node *node, int start)
{
	DIR		*dir;

	dir = opendir(ft_get_env_value(shell, "PWD"));
 	if (!dir)
		return (ft_perror("Cannot open dir!"), -1);
	printf("%s\n", read_dir(shell, dir));
	closedir(dir);
	return (1);
}
