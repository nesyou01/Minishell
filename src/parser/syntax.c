/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:32:13 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/07 23:33:54 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_quotes(char *str)
{
	char	c;

	if (!str)
		return (1);
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			c = *str;
			str++;
			while (*str && *str != c)
				str++;
			if (*str == c)
				str++;
			else
				return (0);
		}
		else
			str++;
	}
	return (1);
}

static int	is_valid_parentheses(t_token *token)
{
	if (token->type == PARENTHESES_START)
		return (token->next && (token->next->type == COMMAND
			|| is_redirection(token->next) || token->next->type == HERE_DOC));
	if (token->type == PARENTHESES_END)
		return (!token->next || (token->next->type != PARENTHESES_START
			&& token->next->type != COMMAND));
	return (1);
}

static int	is_valid_operator(t_token *token)
{
	if (token->type < 100 || token->type == PARENTHESES_START
		|| token->type == PARENTHESES_END)
		return (1);
	return (token->prev && token->prev->type != PIPE
		&& token->prev->type != AND && token->prev->type != OR);
}

int	syntax_validator(t_shell *shell, t_token *token)
{
	while (token)
	{
		if (!is_valid_quotes(token->content))
			return (ft_perror("Unclosed quotes"), 1);
		if (token->type == HERE_DOC
			&& (!token->next || token->next->type != HERE_DOC_LIMITER))
				return (ft_perror("Syntax error near <<"), 1);
		if (!is_valid_parentheses(token) || !is_valid_operator(token))
				return (ft_perror("Syntax error!"), 1);
		if (token->type == HERE_DOC_LIMITER)
		{
			if (here_doc_handler(shell, token))
				return (ft_perror(NULL), 1);
		}
		token = token->next;
	}
	return (0);
}
