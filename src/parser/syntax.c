/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:32:13 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/25 10:13:58 by ylagmah          ###   ########.fr       */
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
	if (token->type != PARENTHESES_START)
		return (1);
	return (!token->prev || token->prev->type >= 100);
}

static int	is_valid_cmd_start(t_token *token)
{
	if (!token->prev)
		return (token->type < 100);
	if (token->prev->type >= 100)
		return (token->type < 100);
	return (1);
}

static int	is_valid_redirection(t_token *token)
{
	if (!is_redirection(token) && token->type != HERE_DOC)
		return (1);
	return (token->next && (token->next->type == FILE || token->next->type == HERE_DOC_LIMITER));
}

int	syntax_validator(t_token *token)
{
	while (token)
	{
		if (!is_valid_quotes(token->content))
			return (ft_perror("Unclosed quotes"), 1);
		if (!is_valid_parentheses(token) || !is_valid_cmd_start(token)
			|| !is_valid_redirection(token))
			return (ft_perror("Syntax error!"), 1);
		token = token->next;
	}
	return (0);
}
