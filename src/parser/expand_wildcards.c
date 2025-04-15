/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:30:31 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/15 13:11:44 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*ft_expand_wildcard(t_shell *shell, char *pattern, char *filter)
{
	DIR		*dir;

	dir = opendir(ft_get_env_value(shell, "PWD"));
	if (!dir)
		return (ft_perror("Cannot open dir!"), NULL);
	return (read_dir(shell, dir, pattern, filter));
}

static int	get_pattern_start(t_node *node)
{
	int		start;
	char	*widlcard;

	widlcard = ft_strchr(node->filter, '2');
	if (!widlcard)
		return (-1);
	start = ft_strlen(node->filter) - ft_strlen(widlcard);
	while (start)
	{
		if (node->filter[start - 1] == ' ')
			break ;
		start--;
	}
	return (start);
}

static char	*build_wildcard_pattern(t_shell *shell, t_list *lst, char *pattern)
{
	char	*str;

	str = NULL;
	if (lst)
	{
		while (lst)
		{
			str = ft_strjoin(shell, str,
					ft_repeat(shell, ft_safe_strlen(lst->content), '0'));
			if (lst->next)
				str = ft_strjoin(shell, str, " ");
			lst = lst->next;
		}
	}
	else
		str = ft_strjoin(shell, str,
				ft_repeat(shell, ft_safe_strlen(pattern), '0'));
	return (str);
}

static int	expand_widlcard(t_shell *shell,
	t_node *node, t_list *result, char *pattern)
{
	int		start;
	int		len;
	char	*start_str;
	char	*end_str;

	start = get_pattern_start(node);
	len = ft_index_of(node->filter + start, ' ');
	pattern = ft_substr(shell, node->content, start, len);
	result = ft_expand_wildcard(shell, pattern,
			ft_substr(shell, node->filter, start, len));
	start_str = ft_substr(shell, node->content, 0, start);
	end_str = ft_substr(shell, node->content,
			start + len, ft_strlen(node->content + start + len));
	if (result)
		start_str = ft_strjoin(shell, start_str, ft_join_all(shell, result));
	else
		start_str = ft_strjoin(shell, start_str, pattern);
	node->content = ft_strjoin(shell, start_str, end_str);
	start_str = ft_substr(shell, node->filter, 0, start);
	end_str = ft_substr(shell, node->filter,
			start + len, ft_strlen(node->filter + start + len));
	start_str = ft_strjoin(shell, start_str,
			build_wildcard_pattern(shell, result, pattern));
	node->filter = ft_strjoin(shell, start_str, end_str);
	return (0);
}

int	ft_wildcard_handler(t_shell *shell, t_node *node)
{
	int	result;

	result = 0;
	while (!result && ft_strchr(node->filter, '2'))
		result = expand_widlcard(shell, node, NULL, NULL);
	return (result);
}
