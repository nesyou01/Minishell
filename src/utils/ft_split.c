/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:45 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/09 22:00:01 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_get_quote_end(char *str, char quote, int start)
{
	int	i;
	int	quotes;

	quotes = 1;
	i = start + quotes;
	while (str[i])
	{
		if (str[i] == quote)
			quotes++;
		if (quotes % 2 == 0 && ft_strchr(SEPECIAL_CHARS, str[i]))
			break ;
		i++;
	}
	return (i);
}

static int	ft_get_token_end(char *str)
{
	int		i;
	char	*first;

	i = 0;
	first = ft_strchr(SEPECIAL_CHARS, *str);
	while (str[i] && str[i] != ' '
		&& (!ft_strchr(SEPECIAL_CHARS, str[i]) == !first))
	{
		if (str[i] == '(' || str[i] == ')')
			return (1);
		if (str[i] == '\'')
			return (ft_get_quote_end(str, '\'', i));
		if (str[i] == '"')
			return (ft_get_quote_end(str, '"', i));
		i++;
	}
	return (i);
}

t_list	*ft_split_node(t_shell *shell, t_node *node)
{
	t_list		*lst;
	int			i;
	int			end;
	char		*content;

	i = 0;
	lst = NULL;
	if (!node->content)
		return (NULL);
	if (!node->content[i])
		return (ft_lstadd_back(&lst, ft_lstnew(shell, node->content)), lst);
	while (node->content[i])
	{
		while (node->filter[i] == ' ')
			i++;
		end = ft_get_token_end(node->filter + i);
		content = ft_substr(shell, node->content, i, end);
		ft_lstadd_back(&lst, ft_lstnew(shell, content));
		i += end;
		while (node->filter[i] == ' ')
			i++;
	}
	return (lst);
}
