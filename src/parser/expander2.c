/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:58:28 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/22 02:01:08 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	set_quotes_filter(t_shell *shell, t_node *node, char *str, int is_empty)
{
	size_t	len;
	char	c;

	len = ft_safe_strlen(str);
	if (is_empty)
		c = 'E';
	else
		c = '0';
	node->filter = ft_strjoin(shell, node->filter, ft_repeat(shell, len, c));
	return (len);
}

int	remove_double_quotes(t_shell *shell, t_node *node, int start, int expand)
{
	char	*start_str;
	char	*end;
	char	*middle;
	char	*expanded;
	int		is_empty;

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
	expanded = middle;
	if (expand)
		expanded = ft_expand_all_vars(shell, middle, 0);
	is_empty = !*expanded;
	if (is_empty)
		expanded = " ";
	node->content = ft_strjoin(shell,
			ft_strjoin(shell, start_str, expanded), end);
	return (set_quotes_filter(shell, node, expanded, is_empty));
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
