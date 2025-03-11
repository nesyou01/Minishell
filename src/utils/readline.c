#include "../../includes/minishell.h"

char	*ft_readline(t_shell *shell, const char *str, int here_doc)
{
	char	*input;

	signals_listener(shell, here_doc);
	input = readline(str);
	signals_listener(shell, 0);
	return (input);
}
