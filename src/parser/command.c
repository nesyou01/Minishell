/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:14:15 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/17 05:18:11 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*ft_parse_command(t_shell *shell, t_node *node)
{
	t_command	*result;
	char		**argv;

	if (!node || node->type != COMMAND)
		return (NULL);
	argv = ft_lst_to_array(shell, ft_split_node(shell, node));
	result = ft_malloc(shell, sizeof(t_command));
	result->envp = ft_get_all_env(shell);
	result->argv = argv;
	result->cmd = argv[0];
	return (result);
}
