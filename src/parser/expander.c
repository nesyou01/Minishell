#include "../../includes/minishell.h"

static int	get_var_end(char *s)
{
	int	i;

	i = 1;
	if (ft_isdigit(s[i]))
	{
		while (s[i] && ft_isdigit(s[i]))
			i++;
	}
	else
	{
		while (s[i] && ft_isalnum(s[i]))
			i++;
	}
	if (s[i])
		i--;
	return (i);
}

static char	*join_all(t_shell *shell, char *s1, t_env *env, char *s3)
{
	char	*result;

	if (env)
	{
		result = ft_strjoin(shell, s1, env->value);
	}
	else
		result = s1;
	result = ft_strjoin(shell, result, s3);
	return (result);
}

static char	*expand_var(t_shell *shell, t_node *node, char *sign)
{
	size_t			total;
	char			*start;
	t_env			*env;
	char			*end;
	size_t			i;

	total = ft_strlen(node->content);
	i = total - ft_strlen(sign);
	if (i)
		start = ft_substr(shell, node->content, 0, i);
	else
		start = NULL;
	i = get_var_end(sign);
	env = ft_get_env(shell->env, ft_substr(shell, sign, 1, i));
	end = ft_substr(shell, sign, i + 1, ft_strlen(sign));
	return (join_all(shell, start, env, end));
}

static void expand_all(t_shell *shell, t_node *node)
{
	char			*sign;

	sign = node->content;
	while (sign)
	{
		ft_remove_quotes(shell, node);
		sign = ft_strchr(sign, '$');
		if (!sign)
			return ;
		if (ft_isalnum(sign[1]))
		{
			node->content = expand_var(shell, node, sign);
			sign = node->content;
		}
		else
			sign++;
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
