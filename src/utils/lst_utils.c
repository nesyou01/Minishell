/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:08:54 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/19 18:09:27 by ylagmah          ###   ########.fr       */
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
