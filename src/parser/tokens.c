/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:45 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/22 15:20:39 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_get_quote_end(char *str, char quote, int start)
{
	int	i;
	int	quotes;

	quotes = 1;
	i = start + quotes;
	while (str[i])
	{
		if (str[i] == quote)
			quotes++;
		if (quotes % 2 == 0
			&& (ft_strchr(SEPECIAL_CHARS, str[i]) || ft_isspace(str[i])))
			break ;
		i++;
	}
	return (i);
}

static int	ft_get_token_end(char *str)
{
	int		i;
	char	*first;

	i = 0;
	first = ft_strchr(SEPECIAL_CHARS, *str);
	while (str[i] && !ft_isspace(str[i])
		&& ((first && str[i] == *str && i < 2)
		|| (!ft_strchr(SEPECIAL_CHARS, str[i]) && !first)))
	{
		if (str[i] == '(' || str[i] == ')')
			return (1);
		if (str[i] == '\'')
			return (ft_get_quote_end(str, '\'', i));
		if (str[i] == '"')
			return (ft_get_quote_end(str, '"', i));
		i++;
	}
	return (i);
}

t_token	*ft_split_tokens(t_shell *shell, char *str)
{
	t_token		*lst;
	int			i;
	int			end;
	char		*content;

	i = 0;
	lst = NULL;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		end = ft_get_token_end(str + i);
		content = ft_substr(shell, str, i, end);
		ft_add_token_last(&lst, ft_new_token(shell, content));
		i += end;
	}
	return (lst);
}
