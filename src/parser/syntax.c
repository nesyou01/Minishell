/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:32:13 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/21 20:13:37 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_operator(t_token *token)
{
	if (token->type < 100 || token->type == PARENTHESES_START
		|| token->type == PARENTHESES_END)
		return (1);
	return (token->prev && token->prev->type != PIPE
		&& token->prev->type != AND && token->prev->type != OR
		&& token->next
		&& (token->next->type == PARENTHESES_START || token->next->type < 100));
}

int	is_valid_file(t_token *token)
{
	if (!is_redirection(token))
		return (1);
	return (token->next && token->next->type == FILE);
}

int	is_valid_cmd(t_token *token)
{
	if (token->type == COMMAND
		|| token->type == FILE
		|| token->type == HERE_DOC_LIMITER)
		return (!token->next || token->next->type != PARENTHESES_START);
	return (1);
}

static int	syntax_validator1(t_token *token)
{
	while (token)
	{
		if (!is_valid_quotes(token->content))
			return (ft_perror("Unclosed quotes"), 9);
		if (!is_valid_file(token)
			|| !is_valid_parentheses(token)
			|| !is_valid_operator(token)
			|| !is_valid_cmd(token))
			return (ft_perror2("Syntax error near", token->content), 258);
		token = token->next;
	}
	return (0);
}

int	syntax_validator(t_shell *shell, t_token *token)
{
	int		first;
	int		status;

	first = syntax_validator1(token);
	if (first == 9)
		return (258);
	status = 0;
	while (token)
	{
		if (!is_valid_here_doc(token))
			return (258);
		if (token->type == HERE_DOC)
		{
			status = here_doc_handler(shell, token->next);
			if (status == 99)
				return (1);
			if (status)
				return (ft_perror("here_doc failed!"), 1);
		}
		token = token->next;
	}
	if (status)
		return (status);
	return (first);
}
