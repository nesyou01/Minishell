#include "../../includes/minishell.h"

static void	malloc_error(t_shell *shell)
{
	ft_clean_all(shell);
	ft_perror("Malloc failed!!!");
	exit(123);
}

void	ft_add_garbage(t_shell *shell, void *ptr)
{
	t_list	*garbage;

	garbage = ft_lstnew(ptr);
	if (!garbage)
	{
		free(ptr);
		malloc_error(shell);
		return ;
	}
	ft_lstadd_front(&(shell->garbage), garbage);
}

void	*ft_malloc(t_shell *shell, size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
		return (malloc_error(shell), NULL);
	ft_add_garbage(shell, result);
	return (result);
}
