/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:11:18 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/12 15:13:56 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*ft_parser(t_shell *shell, char *str)
{
	t_token	*token;
	t_cmd	*cmd;

	cmd = ft_malloc(shell, sizeof(t_cmd));
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->node = NULL;
	token = ft_split_tokens(shell, str);
	ft_tokenize(token);
	ft_merge_tokens(shell, &token);
	ft_merge_args_with_cmd(shell, token);
	if (syntax_validator(token))
		return (NULL);
	ft_tokens_to_nodes(shell, token, cmd);
	ft_remove_quotes(shell, cmd->node);
	ft_node_parser(shell, &(cmd->node));
	ft_to_tree(cmd->node);
	return (cmd);
}
