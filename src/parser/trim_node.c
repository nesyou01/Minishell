/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:50:38 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/17 07:58:09 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	total_size(t_node *node)
{
	size_t	i;
	size_t	size;

	size = 0;
	i = 0;
	while (node->filter[i] && ft_isspace(node->filter[i]))
		i++;
	while (node->filter[i])
	{
		size++;
		i++;
	}
	return (size);
}

static void	set_all(char *filter, char *content, t_node *node, int x)
{
	content[x] = '\0';
	filter[x] = '\0';
	node->content = content;
	node->filter = filter;
}

void	ft_trim_node(t_shell *shell, t_node *node)
{
	char	*result;
	char	*filter;
	size_t	i;
	size_t	x;
	size_t	len;

	i = 0;
	x = 0;
	len = total_size(node);
	if (len == ft_strlen(node->content))
		return ;
	result = ft_malloc(shell, len + 1);
	filter = ft_malloc(shell, len + 1);
	while (node->filter[i] && ft_isspace(node->filter[i]))
		i++;
	while (node->filter[i])
	{
		result[x] = node->content[i - 1];
		filter[x++] = node->filter[i - 1];
	}
	set_all(filter, result, node, x);
}

