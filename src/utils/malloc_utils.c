/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:26:29 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/13 16:26:30 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	malloc_error(t_shell *shell)
{
	ft_clean_all(shell);
	ft_perror("Malloc failed!!!");
	exit(123);
}

void	ft_add_garbage(t_list **head, t_shell *shell, void *ptr)
{
	t_list	*garbage;

	garbage = ft_lstnew(ptr);
	if (!garbage)
	{
		free(ptr);
		malloc_error(shell);
		return ;
	}
	ft_lstadd_front(head, garbage);
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

void	*ft_malloc_globale(t_shell *shell, size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
		return (malloc_error(shell), NULL);
	ft_add_garbage(&(shell->globale_garbage), shell, result);
	return (result);
}
