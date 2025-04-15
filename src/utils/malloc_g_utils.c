/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_g_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:49:05 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/15 12:49:21 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_malloc_globale(t_shell *shell, size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
		return (malloc_error(shell), NULL);
	ft_add_garbage(&(shell->globale_garbage), shell, result);
	return (result);
}
