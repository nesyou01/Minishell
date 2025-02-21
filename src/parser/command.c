/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:02:38 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/21 15:52:58 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*ft_parse_command(t_shell *shell, t_node *node)
{
	t_command	*result;
	t_list		*argv;

	if (node->type != COMMAND)
		return (NULL);
	argv = ft_split(shell, node->content, node->filter);
	result = ft_malloc(shell, sizeof(t_command));
	result->argv = argv;
	result->cmd = argv->content;
	return (result);
}
