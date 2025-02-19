/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:30:31 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/19 20:04:26 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	match(const char *str, const char *pattern)
{
	if (!*pattern && !*str)
		return (1);
	if (*pattern == '*') {
		while (*str) {
			if (match(str, pattern + 1))
				return (1);
			str++;
		}
		return (match(str, pattern + 1));
	}
	if (*pattern == *str)
		return (match(str + 1, pattern + 1));
	return (0);
}

static t_list	*read_dir(t_shell *shell, DIR *dir)
{
	t_list			*list;
	t_list			*node;
 	struct dirent	*dr;

	list = NULL;
 	while (1)
	{
		dr = readdir(dir);
		if (!dr)
			break ;
		if (dr->d_name[0] != '.')
		{
			node = ft_lstnew(shell, dr->d_name);
			ft_lstadd_back(&list, node);
		}
	}
	return (list);
}

static int	ft_expand_wildcards(t_shell *shell, t_node *node)
{
	t_list	*list;
	DIR		*dir;

	dir = opendir(ft_get_env_value(shell, "PWD"));
 	if (!dir)
		return (ft_perror("Cannot open dir!"), -1);
	list = read_dir(shell, dir);
	return (1);
}

int	ft_wildcard_handler(t_shell *shell, t_node *node)
{
	t_list	*lst;
	t_list	*head;

	lst = ft_split(shell, node->content);
	head = lst;
	while (lst)
	{
		ft_expand_list_item(shell, lst);
		lst = lst->next;
	}
	node->content = ft_join_all(shell, head);
	return (0);
}
