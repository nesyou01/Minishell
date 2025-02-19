/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:00 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/19 19:56:23 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_expand_var(t_shell *shell, char **content, int start)
{
	int		end;
	char	*var;
	char	*expanded;
	char	*start_str;
	char	*end_str;
	char	*str;

	str = *content;
	if (!start)
		start_str = NULL;
	else
		start_str = ft_substr(shell, str, 0, start);
	end = get_var_end(str + start) + start + 1;
	var = ft_substr(shell, str, start, end - start);
	expanded = ft_expand_all_vars(shell, var);
	end_str = ft_substr(shell, str, end,
			ft_strlen(str) - end);
	*content = ft_strjoin(shell,
			ft_strjoin(shell, start_str, expanded), end_str);
	return (ft_safe_strlen(expanded));
}

int	ft_remove_double_quotes(t_shell *shell, char **content, int start)
{
	char	*start_str;
	char	*end;
	char	*result;
	char	*middle;
	char	*expanded;
	char	*str;

	str = *content;
	if (!start)
		start_str = NULL;
	else
		start_str = ft_substr(shell, str, 0, start);
	end = ft_strchr(str + start + 1, '"');
	if (end)
		end++;
	middle = ft_substr(shell, str, start + 1,
			ft_safe_strlen(str) - ft_safe_strlen(start_str)
			- ft_safe_strlen(end) - 2);
	expanded = ft_expand_all_vars(shell, middle);
	*content = ft_strjoin(shell,
			ft_strjoin(shell, start_str, expanded), end);
	return (ft_safe_strlen(expanded));
}

int	ft_remove_single_quotes(t_shell *shell, char **content, int start)
{
	char	*start_str;
	char	*end;
	char	*middle;
	char	*str;

	str = *content;
	if (!start)
		start_str = NULL;
	else
		start_str = ft_substr(shell, str, 0, start);
	end = ft_strchr(str + start + 1, '\'');
	if (end)
		end++;
	middle = ft_substr(shell, str, start + 1,
			ft_safe_strlen(str)
			- ft_safe_strlen(start_str) - ft_safe_strlen(end) - 2);
	*content = ft_strjoin(shell,
			ft_strjoin(shell, start_str, middle), end);
	return (ft_safe_strlen(middle));
}

int	ft_expand_node_vars(t_shell *shell, t_node *node)
{
	int		i;
	int		x;

	i = 0;
	if (ft_strchr(node->content, '*'))
		return (ft_wildcard_handler(shell, node));
	while (node->content[i])
	{
		if (node->content[i] == '"')
			x = ft_remove_double_quotes(shell, &(node->content), i);
		else if (node->content[i] == '\'')
			x = ft_remove_single_quotes(shell, &(node->content), i);
		else if (node->content[i] == '$')
			x = ft_expand_var(shell, &(node->content), i);
		else
			x = 1;
		if (x < 0)
			return (1);
		i += x;
	}
	return (0);
}
