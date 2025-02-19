/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widlcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:32:49 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/19 20:06:12 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	join_len(t_list *item)
{
	size_t	size;

	size = 0;
	while (item)
	{
		size += ft_safe_strlen(item->content);
		if (item->next)
			size++;
		item = item->next;
	}
	return (size);
}

char	*ft_join_all(t_shell *shell, t_list *item)
{
	char	*result;
	size_t	i;
	size_t	j;
	
	i = 0;
	j = 0;
	result = ft_malloc(shell, join_len(item) * sizeof(char));
	while (item)
	{
		j = 0;
		while (((char *)item->content)[j])
			result[i++] = ((char *)item->content)[j++];
		if (item->next)
			result[i++] = ' ';
		item = item->next;
	}
	result[i] = '\0';
	return (result);
}

int	ft_expand_list_item(t_shell *shell, t_list *item)
{
	int		i;
	int		x;

	i = 0;
	while (((char *)item->content)[i])
	{
		if (((char *)item->content)[i] == '"')
			x = ft_remove_double_quotes(shell, (char **)&(item->content), i);
		else if (((char *)item->content)[i] == '\'')
			x = ft_remove_single_quotes(shell, (char **)&(item->content), i);
		else if (((char *)item->content)[i] == '$')
			x = ft_expand_var(shell, (char **)&(item->content), i);
		else
			x = 1;
		if (x < 0)
			return (1);
		i += x;
	}
	return (0);
}
