#include "../includes/minishell.h"

static void	on_new_prompt(int signal)
{
	(void) signal;

	exit_status(1, 1);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	on_exit(int signal)
{
	(void) signal;

	printf("\n");
	exit(99);
}

void	signals_listener(int action)
{
	signal(SIGQUIT, SIG_IGN);
	if (action == 0)
		signal(SIGINT, on_new_prompt);
	else if (action == 1)
		signal(SIGINT, on_exit);
	else if (action == 2)
		signal(SIGINT, SIG_IGN);
}
