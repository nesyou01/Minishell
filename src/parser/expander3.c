/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:19:59 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/20 21:20:40 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static int	next_space(char *str, int i)
{
	while (str[i])
	{
		if (ft_isspace(str[i]))
			break ;
		i++;
	}
	return (i);
}

static void	set_quotes(t_shell *shell, t_node *node, int start, int end)
{
	char		*result;
	size_t		i;
	size_t		x;
	size_t		len;

	len = ft_strlen(node->content) + 3;
	result = ft_malloc(shell, len);
	i = 0;
	x = 0;
	while (i < (len - 1))
	{
		if (i == start || i == end)
			result[i] = '"';
		else
			result[i] = node->content[x++];
		i++;
	}
	result[i] = '\0';
	node->content = result;
}

static int	contains_sign(char *str, int i, int end)
{
	while (i < end)
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	add_quotes(t_shell *shell, t_node *node)
{
	int	i;
	int	start;
	int	end;

	if (!node->content || !ft_strchr(node->content, '='))
		return ;
	i = 0;
	start = 0;
	while (node->content[i])
	{
		if (ft_isspace(node->content[i]))
			start = ++i;
		else if (node->content[i] == '=')
		{
			end = next_space(node->content, start);
			if (contains_sign(node->content, i, end))
				set_quotes(shell, node, i + 1, end + 1);
			i++;
		}
		else
			i++;
	}
}
