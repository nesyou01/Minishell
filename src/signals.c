#include "../includes/minishell.h"

static void	on_new_prompt(int signal) {
	printf("\n");
	rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void	signals_listener(t_shell *shell)
{
	if (signal(SIGINT, on_new_prompt) == SIG_ERR)
		ft_error("signal failed");
}