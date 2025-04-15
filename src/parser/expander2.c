/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:58:28 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/15 13:03:58 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	remove_double_quotes(t_shell *shell, t_node *node, int start)
{
	char	*start_str;
	char	*end;
	char	*middle;
	char	*expanded;
	size_t	len;

	node->quotes_expanded = 1;
	if (!start)
		start_str = NULL;
	else
		start_str = ft_substr(shell, node->content, 0, start);
	end = ft_strchr(node->content + start + 1, '"');
	if (end)
		end++;
	middle = ft_substr(shell, node->content, start + 1,
			ft_safe_strlen(node->content) - ft_safe_strlen(start_str)
			- ft_safe_strlen(end) - 2);
	expanded = ft_expand_all_vars(shell, middle);
	node->content = ft_strjoin(shell,
			ft_strjoin(shell, start_str, expanded), end);
	len = ft_safe_strlen(expanded);
	node->filter = ft_strjoin(shell, node->filter, ft_repeat(shell, len, '0'));
	return (len);
}

void	retokinize_export(t_shell *shell, t_node *node)
{
	int		i;
	t_list	*lst;
	int		is_key;

	lst = ft_split_node(shell, node);
	is_key = 1;
	i = 0;
	while (node->content[i])
	{
		if (node->filter[i] == ' ')
		{
			lst = lst->next;
			is_key = 1;
		}
		if (node->content[i] == '=')
			is_key = 0;
		if (node->filter[i] == '2' && ft_strchr(lst->content, '='))
			node->filter[i] = '0';
		if (is_key && node->filter[i] == '0' && node->content[i] == ' ')
			node->filter[i] = ' ';
		i++;
	}
}

static int	is_quote_and_has_end(char *str)
{
	if (*str != '\'' && *str != '"')
		return (0);
	return (ft_strchr(str + 1, *str) != NULL);
}

void	ft_retokenize(t_node *node, int is_export)
{
	int		i;
	char	c;

	i = 0;
	while (node->content[i])
	{
		if (node->filter[i] == '1')
		{
			if (is_quote_and_has_end(node->content + i))
			{
				c = node->content[i];
				node->filter[i++] = '0';
				while (node->filter[i] && node->filter[i] != c)
					node->filter[i++] = '0';
				continue ;
			}
			else if (node->content[i] == '*')
				node->filter[i] = '2';
			else if (!is_export && ft_isspace(node->content[i]))
				node->filter[i] = ' ';
			else
				node->filter[i] = '0';
		}
		i++;
	}
}
