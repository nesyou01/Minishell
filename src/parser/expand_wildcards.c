/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:30:31 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/20 11:18:17 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_match(const char *str, const char *pattern)
{
	if (!*pattern && !*str)
		return (1);
	if (*pattern == '*') {
		while (*str) {
			if (ft_match(str, pattern + 1))
				return (1);
			str++;
		}
		return (ft_match(str, pattern + 1));
	}
	if (*pattern == *str)
		return (ft_match(str + 1, pattern + 1));
	return (0);
}

static int	ft_match_pattern(char *file, char *pattern)
{
	if (*file == '.' && *pattern != '.')
		return (0);
	if (!ft_strcmp(file, ".") || !ft_strcmp(file, ".."))
		return (0);
	return (ft_match(file, pattern));
}

static char	*read_dir(t_shell *shell, DIR *dir, char *pattern)
{
	char			*str;
 	struct dirent	*dr;

	str = NULL;
 	while (1)
	{
		dr = readdir(dir);
		if (!dr)
			break ;
		if (ft_match_pattern(dr->d_name, pattern))
		{
			if (str)
				str = ft_strjoin(shell, str, " ");
			str = ft_strjoin(shell, str, dr->d_name);
		}
	}
	return (str);
}

static int	ft_expand_wildcards(t_shell *shell, t_list *item)
{
	t_list	*list;
	DIR		*dir;

	dir = opendir(ft_get_env_value(shell, "PWD"));
 	if (!dir)
		return (ft_perror("Cannot open dir!"), 2);
	item->content = read_dir(shell, dir, item->content);
	return (item->content == NULL);
}

int	ft_wildcard_handler(t_shell *shell, t_node *node)
{
	t_list	*lst;
	t_list	*head;
	int		result;

	lst = ft_split(shell, node->content);
	head = lst;
	while (lst)
	{
		ft_expand_list_item(shell, lst);
		if (ft_strchr(lst->content, '*'))
		{
			result = ft_expand_wildcards(shell, lst);
			if (result)
				return (result);
		}
		lst = lst->next;
	}
	node->content = ft_join_all(shell, head);
	return (0);
}
