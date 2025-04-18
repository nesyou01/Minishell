/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:45 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/18 10:18:32 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

char	*remove_empty(t_shell *shell, t_node *node, int from, int until)
{
	int		i;
	int		len;
	char	*str;
	int		x;

	x = 0;
	i = from;
	len = 0;
	while (i < until)
	{
		if (node->filter[i] != 'E')
			len++;
		i++;
	}
	str = ft_malloc(shell, (len + 1) * sizeof(char));
	i = from;
	while (i < until)
	{
		if (node->filter[i] != 'E')
			str[x++] = node->content[i];
		i++;
	}
	str[x] = '\0';
	return (str);
}

t_list	*ft_split_node(t_shell *shell, t_node *node)
{
	t_list		*lst;
	int			i;
	int			from;

	i = 0;
	from = 0;
	lst = NULL;
	if (!node || !node->content)
		return (NULL);
	while (node->filter[i])
	{
		while (ft_isspace(node->filter[i]))
			i++;
		if (!node->filter[i])
			break ;
		from = i;
		while (node->filter[i] && !ft_isspace(node->filter[i]))
			i++;
		ft_lstadd_back(&lst,
			ft_lstnew(shell, remove_empty(shell, node, from, i)));
	}
	return (lst);
}
