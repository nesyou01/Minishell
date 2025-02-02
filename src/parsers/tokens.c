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
		if (quotes % 2 == 0 && ft_strchr(SEPECIAL_CHARS, str[i]))
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
	while (str[i] && str[i] != ' '
		&& (!ft_strchr(SEPECIAL_CHARS, str[i]) == !first))
	{
		if (str[i] == '\'')
			return (ft_get_quote_end(str, '\'', i));
		if (str[i] == '"')
			return (ft_get_quote_end(str, '"', i));
		i++;
	}
	return (i);
}

static void	add_new_token(t_shell *shell, t_token **lst, char *str)
{
	t_token	*node;

	node = ft_new_token(shell, str);
	ft_add_token_last(lst, node);
}

t_token	*ft_split_tokens(t_shell *shell, char *str)
{
	t_token	*lst;
	int			i;
	int			end;
	char		*content;

	i = 0;
	lst = NULL;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		end = ft_get_token_end(str + i);
		content = ft_substr(shell, str, i, end);
		add_new_token(shell, &lst, content);
		i += end;
		while (str[i] == ' ')
			i++;
	}
	return (lst);
}
