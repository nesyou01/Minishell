/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:51:28 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/17 14:30:53 by ylagmah          ###   ########.fr       */
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

int	is_valid_parentheses(t_token *token)
{
	if (token->type == PARENTHESES_START)
		return (token->next && (token->next->type == COMMAND
				|| is_redirection(token->next) || token->next->type == HERE_DOC
				|| token->next->type == PARENTHESES_START));
	if (token->type == PARENTHESES_END)
		return (!token->next || (token->next->type != PARENTHESES_START
				&& token->next->type != COMMAND));
	return (1);
}
