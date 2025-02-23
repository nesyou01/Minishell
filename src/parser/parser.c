/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:11:18 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/23 09:12:49 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*ft_parser(t_shell *shell, char *str)
{
	t_token		*token;
	t_node		*node;

	token = ft_split_tokens(shell, str);
	ft_tokenize(token);
	ft_merge_tokens(shell, &token);
	ft_merge_args_with_cmd(shell, token);
	if (syntax_validator(token))
		return (NULL);
	node = ft_tokens_to_nodes(shell, token);
	ft_tree_builder(shell, &node);
	return (node);
}
