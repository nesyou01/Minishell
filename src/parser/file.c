/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:02 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/06 23:52:31 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_file	*ft_new_file(t_shell *shell, t_token *token)
{
	t_file	*file;

	file = (t_file *) ft_malloc(shell, sizeof(t_file));
	file->path = token->content;
	file->fd = token->fd;
	file->type = token->prev->type;
	file->next = NULL;
	return (file);
}

static void	ft_add_file_start(t_file **lst, t_file *new)
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

t_file	*ft_last_file(t_file *lst)
{
	t_file	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_file	*ft_add_file_last(t_file **lst, t_file *new)
{
	t_file	*last;

	if (!new || !lst)
		return (NULL);
	last = ft_last_file(*lst);
	if (!last)
		return (ft_add_file_start(lst, new), new);
	last->next = new;
	return (new);
}

