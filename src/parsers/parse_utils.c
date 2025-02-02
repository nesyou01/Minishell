#include "../../includes/minishell.h"

int	is_redirection(t_token *token)
{
	return (token->type == OUT_REDIRECTER
			|| token->type == IN_REDIRECTER
			|| token->type == OUT_APPEND_REDIRECTER);
}

