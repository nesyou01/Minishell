/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:11:18 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/07 23:34:10 by ylagmah          ###   ########.fr       */
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

static void	read_and_merge(t_shell *shell, t_token *head, t_token *last)
{
	char	*str;
	t_token	*new;

	str = readline(">");
	if (!str)
		return ;
	ft_add_cmd_garbage(shell, str);
	new = parse_all(shell, str);
	last->next = new;
}

t_node	*ft_parser(t_shell *shell, char *str)
{
	t_token		*token;
	t_token		*last;
	t_node		*node;

	token = parse_all(shell, str);
	if (syntax_validator(shell, token))
		return (NULL);
	last = ft_last_token(token);
	if (last && (last->type == PIPE || last->type == AND || last->type == OR))
		read_and_merge(shell, token, last);
	ft_merge_args_with_cmd(shell, token);
	if (syntax_validator(shell, token))
		return (NULL);
	node = ft_tokens_to_nodes(shell, token);
	ft_tree_builder(shell, &node);
	return (node);
}
