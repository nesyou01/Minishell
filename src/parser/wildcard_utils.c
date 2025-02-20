/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:19:05 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/20 20:28:21 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	join_len(t_list *item)
{
	size_t	size;

	size = 0;
	while (item)
	{
		size += ft_safe_strlen(item->content);
		if (item->next)
			size++;
		item = item->next;
	}
	return (size);
}

char	*ft_join_all(t_shell *shell, t_list *item)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!item)
		return (NULL);
	i = 0;
	j = 0;
	result = ft_malloc(shell, join_len(item) * sizeof(char));
	while (item)
	{
		j = 0;
		while (((char *)item->content)[j])
			result[i++] = ((char *)item->content)[j++];
		if (item->next)
			result[i++] = ' ';
		item = item->next;
	}
	result[i] = '\0';
	return (result);
}

void	ft_sort(t_list *lst)
{
	t_list	*tmp;
	char	*t;

	tmp = lst;
	while (tmp)
	{
		if (tmp->next && ft_strcmp(tmp->content, tmp->next->content) > 0)
		{
			t = tmp->next->content;
			tmp->next->content = tmp->content;
			tmp->content = t;
			tmp = lst;
		}
		else
			tmp = tmp->next;
	}
}
