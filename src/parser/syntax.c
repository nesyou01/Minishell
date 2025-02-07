/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:32:13 by ylagmah           #+#    #+#             */
/*   Updated: 2025/01/31 15:10:23 by ylagmah          ###   ########.fr       */
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

int	syntax_validator(t_token *token)
{
	int	par;

	par = 0;
	while (token)
	{
		if (token->type == PARENTHESES_START)
		{
			if (!token->next || token->next->type == PARENTHESES_END)
				return (ft_perror("expected command after '('"), 1);
			par++;
		}
		else if (token->type == PARENTHESES_END)
		{
			if (token->next
				&& (token->next->type != AND_AND || token->next->type != OR_OR))
				return (ft_perror("expected &&/|| after ')'"), 1);
			par--;
		}
		if (!is_valid_quotes(token->content))
			return (ft_perror("unclosed quotes"), 1);
		token = token->next;
	}
	if (par != 0)
		return (ft_perror("syntax error"), 1);
	return (0);
}
