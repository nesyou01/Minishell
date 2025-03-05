/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:02:38 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/05 21:37:55 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*ft_parse_command(t_shell *shell, t_node *node)
{
	t_command	*result;
	char		**argv;

	if (node->type != COMMAND)
		return (NULL);
	result->envp = ft_get_all_env(shell);
	argv = ft_lst_to_array(shell, ft_split_node(shell, node));
	result = ft_malloc(shell, sizeof(t_command));
	result->argv = argv;
	result->cmd = argv[0];
	return (result);
}
