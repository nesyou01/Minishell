/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:39:49 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/22 15:23:45 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell			shell;
	struct termios	initial;

	(void) argv;
	if (argc != 1)
		return (ft_perror("usage => ./minishell"), 1);
	if (ft_any_not_tty())
		return (1);
	if (tcgetattr(STDIN_FILENO, &initial) < 0)
		return (2);
	env_init(&shell, env);
	return (minishell(&shell, &initial));
}
