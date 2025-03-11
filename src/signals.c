#include "../includes/minishell.h"

static void	on_new_prompt(int signal) {
	(void) signal;

	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals_listener(t_shell *shell, int here_doc)
{
	rl_catch_signals = 0;
	if (here_doc)
	{
		if (signal(SIGINT, SIG_DFL) == SIG_ERR
			|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			ft_error(shell, NULL, "signal failed", 99);
	}
	else
	{
		if (signal(SIGINT, on_new_prompt) == SIG_ERR
			|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			ft_error(shell, NULL, "signal failed", 99);
	}
}
