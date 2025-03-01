#include "../../includes/minishell.h"

static size_t	get_env_size(t_env *env)
{
	size_t	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**ft_get_all_env(t_shell *shell)
{
	char	**result;
	size_t	i;
	t_env	*tmp;

	i = 0;
	tmp = shell->env;
	result = ft_malloc(shell, sizeof(char *) * (get_env_size(shell->env) + 1));
	while (tmp)
	{
		result[i++] = ft_strjoin(shell, ft_strjoin(shell, tmp->key, "="), tmp->value);
		tmp = tmp->next;
	}
	result[i] = NULL;
	return (result);
}
