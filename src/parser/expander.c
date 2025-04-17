/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:00 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/17 08:41:30 by ylagmah          ###   ########.fr       */
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
	end = get_var_end(node->content + start) + start + 1;
	var = ft_substr(shell, node->content, start, end - start);
	expanded = ft_expand_all_vars(shell, var);
	end_str = ft_substr(shell, node->content, end,
			ft_strlen(node->content) - end);
	node->content = ft_strjoin(shell,
			ft_strjoin(shell, start_str, expanded), end_str);
	node->filter = ft_strjoin(shell, node->filter,
			ft_repeat(shell, ft_safe_strlen(expanded), '1'));
	return (ft_safe_strlen(expanded));
}

static int	remove_single_quotes(t_shell *shell, t_node *node, int start)
{
	char	*start_str;
	char	*end;
	char	*middle;
	int		is_empty;

	if (!start)
		start_str = NULL;
	else
		start_str = ft_substr(shell, node->content, 0, start);
	end = ft_strchr(node->content + start + 1, '\'');
	if (end)
		end++;
	middle = ft_substr(shell, node->content, start + 1,
			ft_safe_strlen(node->content)
			- ft_safe_strlen(start_str) - ft_safe_strlen(end) - 2);
	if (is_empty)
		middle = " ";
	node->content = ft_strjoin(shell,
			ft_strjoin(shell, start_str, middle), end);
	return (set_quotes_filter(shell, node, middle, is_empty));
}

static int	expand_node_vars(t_shell *shell, t_node *node)
{
	int		i;

	i = 0;
	node->filter = NULL;
	while (node->content[i])
	{
		if (node->content[i] == '"')
			i += remove_double_quotes(shell, node, i, 1);
		else if (node->content[i] == '\'')
			i += remove_single_quotes(shell, node, i);
		else if (node->content[i] == '$')
			i += expand_var(shell, node, i);
		else
		{
			if (node->content[i] == '*')
				node->filter = ft_strjoin(shell, node->filter, "2");
			else if (ft_isspace(node->content[i]))
				node->filter = ft_strjoin(shell, node->filter, " ");
			else
				node->filter = ft_strjoin(shell, node->filter, "0");
			i++;
		}
	}
	return (0);
}

void	ft_remove_quotes(t_shell *shell, t_node *node, int expand)
{
	int		i;

	i = 0;
	node->filter = NULL;
	while (node->content[i])
	{
		if (node->content[i] == '"')
			i += remove_double_quotes(shell, node, i, expand);
		else if (node->content[i] == '\'')
			i += remove_single_quotes(shell, node, i);
		else
		{
			if (node->content[i] == ' ')
				node->filter = ft_strjoin(shell, node->filter, " ");
			else
				node->filter = ft_strjoin(shell, node->filter, "0");
			i++;
		}
	}
}

int	ft_expand_node_vars(t_shell *shell, t_node *node)
{
	int	fail;
	int	is_export;

	if (node->type >= 100 || node->type == EMPTY_CMD)
		return (0);
	fail = expand_node_vars(shell, node);
	if (fail)
		return (1);
	if (ft_strnstr2(node->content, "export", 6))
		retokinize_export(shell, node);
	if (ft_strchr(node->content, '*'))
		fail = ft_wildcard_handler(shell, node);
	if (node->filter && ft_strchr(node->filter, '1'))
	{
		is_export = ft_strnstr2(node->content, "export", 6) != NULL;
		ft_retokenize(node, is_export);
		fail = ft_wildcard_handler(shell, node);
		if (is_export)
			retokinize_export(shell, node);
	}
	if (!fail && node && node->content)
		ft_trim_node(shell, node);
	return (fail);
}
