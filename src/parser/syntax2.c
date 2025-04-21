/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:51:28 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/21 20:12:52 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_quotes(char *str)
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

static int	has_start(t_token *token)
{
	int	ignore;

	ignore = 0;
	token = token->prev;
	while (token)
	{
		if (token->type == PARENTHESES_END)
			ignore++;
		if (token->type == PARENTHESES_START)
		{
			if (!ignore)
				return (1);
			ignore--;
		}
		token = token->prev;
	}
	return (0);
}

static int	has_end(t_token *token)
{
	int	ignore;

	ignore = 0;
	token = token->next;
	while (token)
	{
		if (token->type == PARENTHESES_START)
			ignore++;
		if (token->type == PARENTHESES_END)
		{
			if (!ignore)
				return (1);
			ignore--;
		}
		token = token->next;
	}
	return (0);
}

int	is_valid_parentheses(t_token *token)
{
	if (token->type == PARENTHESES_START)
		return ((token->next && (token->next->type == COMMAND
					|| is_redirection(token->next)
					|| token->next->type == HERE_DOC
					|| token->next->type == PARENTHESES_START))
			&& has_end(token));
	if (token->type == PARENTHESES_END)
		return ((!token->next || (token->next->type != PARENTHESES_START
					&& token->next->type != COMMAND))
			&& has_start(token));
	return (1);
}

int	is_valid_here_doc(t_token *token)
{
	if (!is_valid_parentheses(token)
		|| !is_valid_operator(token)
		|| !is_valid_cmd(token)
		|| !is_valid_file(token))
		return (0);
	if (token->type != HERE_DOC)
		return (1);
	if (!token->next || token->next->type != HERE_DOC_LIMITER)
		return (ft_perror2("Syntax error near", token->content), 0);
	return (1);
}
