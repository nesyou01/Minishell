#include "../../includes/minishell.h"

static size_t	total_size(char *old)
{
	size_t	i;
	size_t	size;

	size = 0;
	i = 0;
	while (old[i] && ft_isspace(old[i]))
		i++;
	while (old[i])
	{
		if (!ft_isspace(old[i]))
		{
			if (i >= 1 && ft_isspace(old[i - 1]))
				size++;
			size++;
		}
		i++;
	}
	return (size);
}

char	*ft_trim_var(t_shell *shell, char *old)
{
	char 	*result;
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	result = ft_malloc(shell, total_size(old) + 1);
	while (old[i] && ft_isspace(old[i]))
		i++;
	while (old[i])
	{
		if (!ft_isspace(old[i]))
		{
			if (x > 0 && ft_isspace(old[i - 1]))
				result[x++] = ' ';
			result[x++] = old[i];
		}
		i++;
	}
	result[x] = '\0';
	return (result);
}
