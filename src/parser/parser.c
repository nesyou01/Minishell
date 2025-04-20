/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:11:18 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/20 03:25:26 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*parse_all(t_shell *shell, char *str)
{
	t_token		*token;

	token = ft_split_tokens(shell, str);
	ft_tokenize(token);
	ft_merge_tokens(shell, &token);
	return (token);
}

static void	close_all(t_token *token)
{
	while (token)
	{
		if (token->fd != -1)
			close(token->fd);
		token = token->next;
	}
}

t_node	*ft_parser(t_shell *shell, char *str)
{
	t_token		*token;
	t_node		*node;
	int			status;

	token = parse_all(shell, str);
	status = syntax_validator(shell, token);
	if (status)
		return (exit_status(1, status), close_all(token), NULL);
	ft_merge_args_with_cmd(shell, token);
	node = ft_tokens_to_nodes(shell, token);
	ft_tree_builder(shell, &node);
	return (node);
}
