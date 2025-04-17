/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:03:47 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/17 08:31:36 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_match(char *str, char *pattern, char *filter)
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
		{
			x++;
			y++;
		}
		else if (x_last != -1)
			x = ++x_last;
		else
			break ;
	}
	return (!str[x] && !pattern[y]);
}

int	ft_match_pattern(char *file, char *pattern, char *filter)
{
	if (*file == '.' && *pattern != '.')
		return (0);
	return (ft_match(file, pattern, filter));
}

t_list	*read_dir(t_shell *shell, DIR *dir, char *pattern, char *filter)
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
			ft_lstadd_back(&lst, ft_lstnew(shell, ft_strdup(shell, dr->d_name)));
	}
	ft_sort(lst);
	closedir(dir);
	return (lst);
}
