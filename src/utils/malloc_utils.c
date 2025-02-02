#include "../../includes/minishell.h"

static void	malloc_error(t_shell *shell)
{
	ft_clean_all(shell);
	ft_perror("Malloc failed!!!");
	exit(123);
}

void	*ft_malloc(t_shell *shell, size_t size)
{
	void	*result;
	t_list	*garbage;

	result = malloc(size);
	if (!result)
		return (malloc_error(shell), NULL);
	garbage = ft_lstnew(result);
	if (!garbage)
		return (free(result), malloc_error(shell), NULL);
	ft_lstadd_back(&(shell->garbage), garbage);
	return (result);
}
