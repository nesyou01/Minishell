/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:11:18 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/17 13:15:26 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_execute	*ft_parser(t_shell *shell, char *str)
{
	t_token		*token;
	t_execute	*cmd;

	cmd = ft_malloc(shell, sizeof(t_execute));
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->node = NULL;
	cmd->here_doc = NULL;
	token = ft_split_tokens(shell, str);
	ft_tokenize(token);
	ft_merge_tokens(shell, &token);
	ft_merge_args_with_cmd(shell, token);
	if (syntax_validator(token))
		return (NULL);
	ft_tokens_to_nodes(shell, token, cmd);
	ft_node_parser(shell, &(cmd->node));
	ft_to_tree(cmd->node);
	return (cmd);
}
