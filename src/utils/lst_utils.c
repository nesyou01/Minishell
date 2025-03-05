/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:08:54 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/05 21:37:19 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_lstnew(t_shell *shell, void *content)
{
	t_list	*new;

	new = ft_malloc(shell, sizeof(t_list));
	new->content = content;
	new->next = NULL;
	return (new);
}

char	**ft_lst_to_array(t_shell *shell, t_list *lst)
{
	char	**result;
	int		i;

	i = 0;
	result = ft_malloc(shell, (ft_lstsize(lst) + 1) * sizeof(char *));
	while (lst)
	{
		result[i++] = lst->content;
		lst = lst->next;
	}
	result[i] = NULL;
	return (result);
}
