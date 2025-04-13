/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:30:31 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/13 16:29:28 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_match(char *str, char *pattern, char *filter)
{
	int	x;
	int	y;
	int	x_last;

	x = 0;
	y = 0;
	x_last = -1;
	while (str[x] || filter[y] == '2')
	{
		if (filter[y] == '2')
		{
			x_last = x;
			y++;
		}
		else if (str[x] == pattern[y])
			(x++, y++);
		else if (x_last != -1)
			x = ++x_last;
		else
			break ;
	}
	return (!str[x] && !pattern[y]);
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
			str = ft_strjoin(shell, str, ft_repeat(shell, ft_safe_strlen(lst->content), '0'));
			if (lst->next)
				str = ft_strjoin(shell, str, " ");
			lst = lst->next;
		}
	}
	else
		str = ft_strjoin(shell, str, ft_repeat(shell, ft_safe_strlen(pattern), '0'));
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
	len = ft_index_of(node->filter + start, ' ');
	pattern = ft_substr(shell, node->content, start, len);
	filter = ft_substr(shell, node->filter, start, len);
	result = ft_expand_wildcard(shell, pattern, filter);
	start_str = ft_substr(shell, node->content, 0, start);
	end_str = ft_substr(shell, node->content, start + len, ft_strlen(node->content + start + len));
	if (result)
		start_str = ft_strjoin(shell, start_str, ft_join_all(shell, result));
	else
		start_str = ft_strjoin(shell, start_str, pattern);
	node->content = ft_strjoin(shell, start_str, end_str);
	start_str = ft_substr(shell, node->filter, 0, start);
	end_str = ft_substr(shell, node->filter, start + len, ft_strlen(node->filter + start + len));
	start_str = ft_strjoin(shell, start_str, build_wildcard_pattern(shell, result, pattern));
	node->filter = ft_strjoin(shell, start_str, end_str);
	return (0);
}

static int	is_quote_and_has_end(char *str)
{
	if (*str != '\'' && *str != '"')
		return (0);
	return (ft_strchr(str + 1, *str) != NULL);
}

void	ft_retokenize(t_node *node)
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
	return (result);
}
