#include "../../includes/minishell.h"

static int	first_quote(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (*str);
		str++;
	}
	return (-1);
}

static char	*remove_all(t_shell *shell, char *str, int c)
{
	size_t	c_count;
	size_t	i;
	char	*result;
	size_t	x;

	x = 0;
	i = 0;
	c_count = 0;
	while (str[i])
	{
		if (str[i] == c)
			c_count++;
		i++;
	}
	i = 0;
	result = ft_malloc(shell, ft_strlen(str) - c_count + 1);
	while (str[i])
	{
		if (str[i] != c)
			result[x++] = str[i];
		i++;
	}
	result[x] = '\0';
	return (result);
}

void	ft_remove_quotes(t_shell *shell, t_node *node)
{
	int	c;

	while (node)
	{
		c = first_quote(node->content);
		if (c != -1)
			node->content = remove_all(shell, node->content, c);
		node = node->next;
	}
}
