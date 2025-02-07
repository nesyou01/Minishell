/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:35:05 by ylagmah           #+#    #+#             */
/*   Updated: 2025/01/29 14:18:45 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_new_cmd(t_token *token)
{
	return (!token->prev || token->prev->type == PIPE
		|| token->prev->type == PARENTHESES_START
		|| token->prev->type == AND_AND
		|| token->prev->type == OR_OR);
}

static int	is_first_cmd(t_token *token)
{
	while (token)
	{
		if (token->type == COMMAND)
			return (0);
		if (token->type >= 100)
			return (1);
		token = token->prev;
	}
	return (1);
}

static int	get_token_type_extra(t_token *token)
{
	if (is_new_cmd(token))
		return (COMMAND);
	if (token->prev->type == IN_REDIRECTER)
		return (FILE);
	if (token->prev->type == HERE_DOC)
		return (HERE_DOC_LIMITER);
	if (token->prev->type == OUT_REDIRECTER
		|| token->prev->type == OUT_APPEND_REDIRECTER)
		return (FILE);
	if (token->prev->type == COMMAND
		|| token->prev->type == ARGUMENT)
		return (ARGUMENT);
	if (is_first_cmd(token))
		return (COMMAND);
	return (UNKNOWN);
}

static int	get_token_type(t_token *token)
{
	if (!ft_strcmp(token->content, "|"))
		return (PIPE);
	if (!ft_strcmp(token->content, ">"))
		return (OUT_REDIRECTER);
	if (!ft_strcmp(token->content, "<"))
		return (IN_REDIRECTER);
	if (!ft_strcmp(token->content, "<<"))
		return (HERE_DOC);
	if (!ft_strcmp(token->content, ">>"))
		return (OUT_APPEND_REDIRECTER);
	if (!ft_strcmp(token->content, "$?"))
		return (STATUS_CODE);
	if (!ft_strcmp(token->content, "("))
		return (PARENTHESES_START);
	if (!ft_strcmp(token->content, ")"))
		return (PARENTHESES_END);
	if (!ft_strcmp(token->content, "&&"))
		return (AND_AND);
	if (!ft_strcmp(token->content, "||"))
		return (OR_OR);
	return (get_token_type_extra(token));
}

int	ft_tokenize(t_token *lst)
{
	while (lst)
	{
		lst->type = get_token_type(lst);
		lst = lst->next;
	}
	return (0);
}
