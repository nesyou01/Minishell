/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:00 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/16 12:16:22 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expand_var(t_shell *shell, t_node *node, int start)
{
	int		end;
	char	*var;
	char	*expanded;
	char	*start_str;
	char	*end_str;

	if (!start)
		start_str = NULL;
	else
		start_str = ft_substr(shell, node->content, 0, start);
	end = get_var_end(node->content + start) + 1;
	var = ft_substr(shell, node->content, start, end);
	expanded = ft_expand_all_vars(shell, var);
	end_str = ft_substr(shell, node->content, end, ft_strlen(node->content) - end);
	node->content = ft_strjoin(shell, ft_strjoin(shell, start_str, expanded), end_str);
	return (1);
}

static int	remove_double_quotes(t_shell *shell, t_node *node, int start)
{
	char	*start_str;
	char	*end;
	char	*result;
	char	*middle;
	char	*expanded;

	if (!start)
		start_str = NULL;
	else
		start_str = ft_substr(shell, node->content, 0, start);
	end = ft_strchr(node->content + start + 1, '"');
	if (end)
		end++;
	middle = ft_substr(shell, node->content, start + 1,
		ft_safe_strlen(node->content) - ft_safe_strlen(start_str) - ft_safe_strlen(end) - 2);
	expanded = ft_expand_all_vars(shell, middle);
	node->content = ft_strjoin(shell, ft_strjoin(shell, start_str, expanded), end);
	return (ft_safe_strlen(expanded));
}

static int	remove_single_quotes(t_shell *shell, t_node *node, int start)
{
	char	*start_str;
	char	*end;
	char	*middle;

	if (!start)
		start_str = NULL;
	else
		start_str = ft_substr(shell, node->content, 0, start);
	end = ft_strchr(node->content + start + 1, '\'');
	if (end)
		end++;
	middle = ft_substr(shell, node->content, start + 1,
		ft_safe_strlen(node->content) - ft_safe_strlen(start_str) - ft_safe_strlen(end) - 2);
	node->content = ft_strjoin(shell, ft_strjoin(shell, start_str, middle), end);
	return (ft_safe_strlen(middle));
}

static void	expand_all(t_shell *shell, t_node *node)
{
	int	i;

	i = 0;
	while (node->content[i])
	{
		if (node->content[i] == '\"')
			i += remove_double_quotes(shell, node, i);
		else if (node->content[i] == '\'')
			i += remove_single_quotes(shell, node, i);
		else if (node->content[i] == '$')
			i += expand_var(shell, node, i);
		else
			i++;
	}
}

void	ft_expander(t_shell *shell, t_node *node)
{
	while (node)
	{
		expand_all(shell, node);
		node = node->next;
	}
}
