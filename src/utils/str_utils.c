#include "../../includes/minishell.h"

char	*ft_strstrchr(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (ft_strchr(s2, s1[i]))
			return ((char *)((s1 + i)));
		i++;
	}
	return (NULL);
}

