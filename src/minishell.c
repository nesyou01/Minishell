/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:35:32 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/13 14:48:40 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	minishell(t_shell *shell)
{
	char		*str;
	t_cmd		*cmd;

	while (!shell->exit)
	{
		str = readline("\033[32mminishell >> \033[0m");
		ft_add_garbage(&(shell->cmd_garbage), shell, str);

		cmd = ft_parser(shell, str);
		if (cmd)
			ft_execute(shell, cmd->node);
		ft_clean_cmd(shell);
	}
	ft_clean_all(shell);
}

void f()
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	atexit(f);
	(void) argv;
	if (argc != 1)
		return (ft_perror("usage => ./minishell"), 1);
	env_init(&shell, env);
	shell.exit = 0;
	minishell(&shell);
	return (0);
}
