/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:11:18 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/11 23:50:59 by ylagmah          ###   ########.fr       */
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

static void	read_and_merge(t_shell *shell, t_token *head, t_token *last, char **old)
{
	char	*str;
	t_token	*new;

	str = readline("> ");
	if (!str)
		return ;
	ft_add_cmd_garbage(shell, str);
	*old = ft_strjoin(shell, *old, ft_strjoin(shell, " ", str));
	new = parse_all(shell, str);
	last->next = new;
}

static int	should_merge(t_token *last, t_token *head)
{
	return (last->type == PIPE || last->type == AND || last->type == OR);
}

static int	is_valid_end(t_token *token)
{
	t_token		*last;

	last = ft_last_token(token);
	return (last == NULL || last->type == PARENTHESES_END || last->type < 100);
}

t_node	*ft_parser(t_shell *shell, char **str)
{
	t_token		*token;
	t_token		*last;
	t_node		*node;

	token = parse_all(shell, *str);
	if (syntax_validator(shell, token))
		return (NULL);
	last = ft_last_token(token);
	if (last && should_merge(last, token))
		read_and_merge(shell, token, last, str);
	ft_merge_args_with_cmd(shell, token);
	if (syntax_validator(shell, token))
		return (NULL);
	if (ft_repeat_count(token, PARENTHESES_START)
		!= ft_repeat_count(token, PARENTHESES_END) || !is_valid_end(token))
		return (ft_perror2("syntax error near", "EOF"), NULL);
	node = ft_tokens_to_nodes(shell, token);
	ft_tree_builder(shell, &node);
	return (node);
}
