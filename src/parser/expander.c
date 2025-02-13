#include "../../includes/minishell.h"

static int	get_var_end(char *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i + 1]))
			return (i);
		i++;
	}
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

static void expand_all(t_shell *shell, t_node *node)
{
	char			*sign;
	size_t			total;
	char			*start;
	t_env			*env;
	char			*end;
	size_t			i;

	sign = ft_strchr(node->content, '$');
	if (!sign)
		return ;
	while (sign)
	{
		total = ft_strlen(node->content);
		i = total - ft_strlen(sign);
		if (i)
			start = ft_substr(shell, node->content, 0, i);
		else
			start = NULL;
		i = get_var_end(node->content) + 1;
		env = ft_get_env(shell->env, ft_substr(shell, sign, 1, i));
		end = ft_substr(shell, sign, i, ft_strlen(sign));
		node->content = join_all(shell, start, env, end);
		sign = ft_strchr(node->content, '$');
	}
}

void	ft_expander(t_shell *shell, t_node *node)
{
	while (node)
	{
		ft_remove_quotes(shell, node);
		expand_all(shell, node);
		node = node->next;
	}
}
