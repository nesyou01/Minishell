/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:07:50 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/15 18:52:53 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	ft_onexit(int signal)
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
		signal(SIGINT, ft_onexit);
	else if (action == 2)
		signal(SIGINT, SIG_IGN);
	else if (action == 3)
		signal(SIGINT, SIG_ERR);
}
