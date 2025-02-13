/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:02 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/13 16:27:03 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_file	*ft_new_file(t_shell *shell, char *path)
{
	t_file	*file;

	file = (t_file *) ft_malloc(shell, sizeof(t_file));
	file->path = path;
	file->fd = -1;
	file->next = NULL;
	return (file);
}

void	ft_add_file_start(t_file **lst, t_file *new)
{
	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

t_file	*get_file_or_add(t_shell *shell, char *path)
{
	t_file	*tmp;

	tmp = shell->file;
	while (tmp)
	{
		if (ft_strcmp(tmp->path, path) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_new_file(shell, path);
	ft_add_file_start(&(shell->file), tmp);
	return (tmp);
}
