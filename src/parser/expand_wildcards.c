/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:30:31 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/21 15:48:42 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_match(char *str, char *pattern, char *filter)
{
	if (!*pattern && !*str)
		return (1);
	if (*filter == '2') {
		while (*str) {
			if (ft_match(str, pattern + 1, filter + 1))
				return (1);
			str++;
		}
		return (ft_match(str, pattern + 1, filter + 1));
	}
	if (*pattern == *str)
		return (ft_match(str + 1, pattern + 1, filter + 1));
	return (0);
}

static int	ft_match_pattern(char *file, char *pattern, char *filter)
{
	if (*file == '.' && *pattern != '.')
		return (0);
	return (ft_match(file, pattern, filter));
}

static t_list	*read_dir(t_shell *shell, DIR *dir, char *pattern, char *filter)
{
	t_list			*lst;
 	struct dirent	*dr;

	lst = NULL;
 	while (1)
	{
		dr = readdir(dir);
		if (!dr)
			break ;
		if (ft_match_pattern(dr->d_name, pattern, filter))
			ft_lstadd_back(&lst, ft_lstnew(shell, dr->d_name));
	}
	ft_sort(lst);
	return (lst);
}

static t_list	*ft_expand_wildcard(t_shell *shell, char *pattern, char *filter)
{
	t_list	*result;
	DIR		*dir;

	dir = opendir(ft_get_env_value(shell, "PWD"));
 	if (!dir)
		return (ft_perror("Cannot open dir!"), NULL);
	result = read_dir(shell, dir, pattern, filter);
 	if (!result)
		ft_perror("No matches!!");
	return (result);
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

static char	*build_wildcard_pattern(t_shell *shell, t_list *lst)
{
	char	*str;

	str = NULL;
	while (lst)
	{
		str = ft_strjoin(shell, str, ft_repeat(shell, ft_safe_strlen(lst->content), '0'));
		if (lst->next)
			str = ft_strjoin(shell, str, " ");
		lst = lst->next;
	}
	return (str);
}

static int	expand_widlcard(t_shell *shell, t_node *node)
{
	int		start;
	int		len;
	char	*pattern;
	char	*filter;
	t_list	*result;
	char	*start_str;
	char	*end_str;

	start = get_pattern_start(node);
	len = ft_index_of(node->content + start, ' ');
	pattern = ft_substr(shell, node->content, start, len);
	filter = ft_substr(shell, node->filter, start, len);
	result = ft_expand_wildcard(shell, pattern, filter);
	if (!result)
		return (1);
	start_str = ft_substr(shell, node->content, 0, start);
	end_str = ft_substr(shell, node->content, start + len, ft_strlen(node->content + start + len));
	start_str = ft_strjoin(shell, start_str, ft_join_all(shell, result));
	node->content = ft_strjoin(shell, start_str, end_str);
	start_str = ft_substr(shell, node->filter, 0, start);
	end_str = ft_substr(shell, node->filter, start + len, ft_strlen(node->filter + start + len));
	start_str = ft_strjoin(shell, start_str, build_wildcard_pattern(shell, result));
	node->filter = ft_strjoin(shell, start_str, end_str);
	return (0);
}

static void	retokenize(t_node *node)
{
	int		i;
	char	c;

	i = 0;
	while (node->content[i])
	{
		if (node->filter[i] == '1')
		{
			if (node->content[i] == '\'' || node->content[i] == '"')
			{
				c = node->content[i];
				node->filter[i++] = '0';
				while (node->filter[i] && node->filter[i] != c)
					node->filter[i++] = '0';
				continue ;
			}
			else if (node->content[i] == ' ')
					node->filter[i] = ' ';
			else if (node->content[i] == '*')
					node->filter[i] = '2';
			else
				node->filter[i] = '0';
		}
		i++;
	}
}

int	ft_wildcard_handler(t_shell *shell, t_node *node)
{
	int	result;

	result = 0;
	while (!result && ft_strchr(node->filter, '2'))
		result = expand_widlcard(shell, node);
	if (result)
		return (result);
	if (ft_strchr(node->filter, '1'))
	{
		retokenize(node);
		ft_wildcard_handler(shell, node);
	}
	return (result);
}
