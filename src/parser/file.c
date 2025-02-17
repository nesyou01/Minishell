/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:02 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/17 17:05:05 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_file	*ft_new_file(t_shell *shell, char *path)
{
	t_file	*file;

	file = (t_file *) ft_malloc(shell, sizeof(t_file));
	file->path = path;
	file->fd = -1;
	return (file);
}

