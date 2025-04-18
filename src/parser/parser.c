/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:11:18 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/18 12:36:11 by ylagmah          ###   ########.fr       */
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
	status = syntax_validator(shell, token);
	if (status)
		return (exit_status(1, status), NULL);
	if (ft_repeat_count(token, PARENTHESES_START)
		!= ft_repeat_count(token, PARENTHESES_END) || !is_valid_end(token))
	{
		ft_perror2("syntax error near", "EOF");
		return (exit_status(1, 258), NULL);
	}
	node = ft_tokens_to_nodes(shell, token);
	ft_tree_builder(shell, &node);
	return (node);
}
