/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:33:36 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/17 17:38:22 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*sub_str_until(t_shell *shell, char *str, char c)
{
	int	until;

	until = 0;
	while (str[until] && until != c)
		until++;
	if (!until)
		return (NULL);
	return (ft_substr(shell, str, 0, until + 1));
}

static int	ft_matches(char *str, char *filter, int from)
{
	size_t	f_len;
	int		s;

	if (!filter)
		return (1);
	if (from == 0)
		return (ft_strnstr(str, filter, ft_strlen(filter)) != NULL);
	if (from == 2)
	{
		f_len = ft_strlen(filter);
		s = ft_strlen(str) - f_len;
		if (s <= 0)
			return (0);
		return (ft_strnstr(str + s, filter, f_len) != NULL);
	}
	return (ft_strnstr(str, filter, ft_strlen(str)) != NULL);
}

static char	*read_dir(t_shell *shell, DIR *dir, char *filter)
{
	char			*str;
 	struct dirent	*dr;

	str = NULL;
 	while (1)
	{
		dr = readdir(dir);
		if (!dr)
			break ;
		if (dr->d_name[0] != '.' && ft_matches(dr->d_name, filter, 2))
		{
			if (str)
				str = ft_strjoin(shell, str, " ");
			str = ft_strjoin(shell, str, dr->d_name);
		}
	}
	return (str);
}

int	ft_expand_wildcards(t_shell *shell, t_node *node, int start)
{
	DIR		*dir;
	char	*filter;
	char	*expanded;
	char	*start_str;
	char	*end;
	
	dir = opendir(ft_get_env_value(shell, "PWD"));
 	if (!dir)
		return (ft_perror("Cannot open dir!"), -1);
	filter = sub_str_until(shell, node->content + start + 1, ' ');
	expanded = read_dir(shell, dir, filter);
	closedir(dir);
	if (!expanded)
		return (ft_safe_strlen(filter) + 1);
	if (!start)
		start_str = NULL;
	else
		start_str = ft_substr(shell, node->content, 0, start);
	end = node->content + start + ft_safe_strlen(filter) + 1;
	node->content = ft_strjoin(shell,
			ft_strjoin(shell, start_str, expanded), end);
	return (ft_safe_strlen(expanded));
}
