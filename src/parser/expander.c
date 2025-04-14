/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:00 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/14 16:30:47 by ylagmah          ###   ########.fr       */
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
	size_t	len;

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
	len = ft_safe_strlen(expanded);
	node->filter = ft_strjoin(shell, node->filter, ft_repeat(shell, len, '1'));
	return (len);
}

static int	remove_double_quotes(t_shell *shell, t_node *node, int start)
{
	char	*start_str;
	char	*end;
	char	*middle;
	char	*expanded;
	size_t	len;

	node->quotes_expanded = 1;
	if (!start)
		start_str = NULL;
	else
		start_str = ft_substr(shell, node->content, 0, start);
	end = ft_strchr(node->content + start + 1, '"');
	if (end)
		end++;
	middle = ft_substr(shell, node->content, start + 1,
			ft_safe_strlen(node->content) - ft_safe_strlen(start_str)
			- ft_safe_strlen(end) - 2);
	expanded = ft_expand_all_vars(shell, middle);
	node->content = ft_strjoin(shell,
			ft_strjoin(shell, start_str, expanded), end);
	len = ft_safe_strlen(expanded);
	node->filter = ft_strjoin(shell, node->filter, ft_repeat(shell, len, '0'));
	return (len);
}

static int	remove_single_quotes(t_shell *shell, t_node *node, int start)
{
	char	*start_str;
	char	*end;
	char	*middle;
	size_t	len;

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
	node->content = ft_strjoin(shell,
			ft_strjoin(shell, start_str, middle), end);
	len = ft_safe_strlen(middle);
	node->filter = ft_strjoin(shell, node->filter, ft_repeat(shell, len, '0'));
	return (len);
}

static int	expand_node_vars(t_shell *shell, t_node *node)
{
	int		i;

	i = 0;
	node->filter = NULL;
	while (node->content[i])
	{
		if (node->content[i] == '"')
			i += remove_double_quotes(shell, node, i);
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

void	ft_remove_quotes(t_shell *shell, t_node *node)
{
	int		i;

	i = 0;
	node->filter = NULL;
	while (node->content[i])
	{
		if (node->content[i] == '"')
			i += remove_double_quotes(shell, node, i);
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
static void	retokinize_export(t_shell *shell, t_node *node)
{
	int		i;
	t_list	*lst;
	int		is_key;

	// if (!ft_strchr(node->filter, '2'))
	// 	return ;
	lst = ft_split_node(shell, node);
	is_key = 1;
	i = 0;
	while (node->content[i])
	{
		if (node->filter[i] == ' ')
		{
			lst = lst->next;
			is_key = 1;
		}
		if (node->content[i] == '=')
			is_key = 0;
		if (node->filter[i] == '2' && ft_strchr(lst->content, '='))
			node->filter[i] = '0';
		if (is_key && node->filter[i] == '0' && node->content[i] == ' ')
			node->filter[i] = ' ';
		i++;
	}
}

int	ft_expand_node_vars(t_shell *shell, t_node *node)
{
	int	fail;

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
		ft_retokenize(node);
		fail = ft_wildcard_handler(shell, node);
		if (ft_strnstr2(node->content, "export", 6))
			retokinize_export(shell, node);
	}
	if (!(node->content[0]) && !node->quotes_expanded)
		node->content = NULL;
	return (fail);
}
