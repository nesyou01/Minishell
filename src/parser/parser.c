/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:11:18 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/18 21:16:08 by ylagmah          ###   ########.fr       */
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

static int	is_valid_end(t_token *token)
{
	t_token		*last;

	last = ft_last_token(token);
	return (last == NULL || last->type == PARENTHESES_END || last->type < 100);
}

t_node	*ft_parser(t_shell *shell, char *str)
{
	t_token		*token;
	t_node		*node;
	int			status;

	token = parse_all(shell, str);
	status = syntax_validator(shell, token);
	if (status)
		return (exit_status(1, status), NULL);
	ft_merge_args_with_cmd(shell, token);
	node = ft_tokens_to_nodes(shell, token);
	ft_tree_builder(shell, &node);
	return (node);
}
