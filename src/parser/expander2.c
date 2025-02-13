/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:20:58 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/13 14:30:38 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	first_quote(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (*str);
		str++;
	}
	return (-1);
}

static size_t	quotes_count(char *str, char c)
{
	size_t	c_count;
	size_t	i;

	i = 0;
	c_count = 0;
	while (str[i])
	{
		if (str[i] == c)
			c_count++;
		i++;
	}
	return (c_count);
}

void	ft_remove_quotes(t_shell *shell, t_node *node)
{
	size_t	i;
	char	c;
	size_t	c_count;
	char	*result;
	size_t	x;


	c = first_quote(node->content);
	if (c == -1)
		return ;
	c_count = quotes_count(node->content, c);
	x = 0;
	i = 0;
	result = ft_malloc(shell, ft_strlen(node->content) - c_count + 1);
	while (node->content[i] && node->content[i] != '$')
	{
		if (node->content[i] != c)
			result[x++] = node->content[i];
		i++;
	}
	result[x] = '\0';
	node->content = result;
}
