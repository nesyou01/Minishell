/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:45 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/17 07:59:48 by ylagmah          ###   ########.fr       */
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

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	get_next_break(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'E')
			return (i + 1);
		if (ft_isspace(str[i]))
			return (i);
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
	if (!node || !node->content)
		return (NULL);
	while (node->filter[i])
	{
		if (ft_isspace(node->filter[i]))
			i++;
		if (node->filter[i] == 'E')
			(ft_lstadd_back(&lst, ft_lstnew(shell, ft_strdup(shell, ""))), i++);
		else
		{
			end = get_next_break(node->filter + i);
			content = ft_substr(shell, node->content, i, end);
			ft_lstadd_back(&lst, ft_lstnew(shell, content));
			i += end;
		}
	}
	return (lst);
}
