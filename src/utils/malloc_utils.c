/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:26:29 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/15 12:55:36 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*ft_new_garbage(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	malloc_error(t_shell *shell)
{
	ft_clean_all(shell, NULL);
	ft_perror("Malloc failed!!!");
	exit(1);
}

void	ft_add_garbage(t_list **head, t_shell *shell, void *ptr)
{
	t_list	*garbage;

	garbage = ft_new_garbage(ptr);
	if (!garbage)
	{
		free(ptr);
		malloc_error(shell);
		return ;
	}
	ft_lstadd_front(head, garbage);
}

void	ft_add_cmd_garbage(t_shell *shell, void *ptr)
{
	ft_add_garbage(&(shell->cmd_garbage), shell, ptr);
}

void	*ft_malloc(t_shell *shell, size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
		return (malloc_error(shell), NULL);
	ft_add_garbage(&(shell->cmd_garbage), shell, result);
	return (result);
}
