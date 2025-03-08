/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:34:22 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/07 23:54:08 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_last_token(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_add_token_start(t_token **lst, t_token *new)
{
	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	(*lst)->prev = new;
	new->next = *lst;
	*lst = new;
}

t_token	*ft_new_token(t_shell *shell, char	*content)
{
	t_token	*list;

	list = (t_token *) ft_malloc(shell, sizeof(t_token));
	list->content = content;
	list->type = UNKNOWN;
	list->fd = -1;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

void	ft_add_token_last(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!new || !lst)
		return ;
	last = ft_last_token(*lst);
	if (!last)
		return (ft_add_token_start(lst, new));
	last->next = new;
	new->prev = last;
}

int	ft_repeat_count(t_token *head, int type)
{
	int	count;

	count = 0;
	while (head)
	{
		if (head->type == type)
			count++;
		head = head->next;
	}
	return (count);
}
