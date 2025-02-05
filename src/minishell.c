/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:35:32 by ylagmah           #+#    #+#             */
/*   Updated: 2025/01/31 15:09:43 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell(t_shell *shell)
{
	char		*str;
	t_cmd		*cmd;

	while (!shell->exit)
	{
		str = readline("\033[32mminishell >> \033[0m");
		ft_add_garbage(shell, str);
		cmd = ft_parser(shell, str);
		ft_clean_all(shell);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void) argc;
	(void) argv;
	env_init(&shell, env);
	shell.exit = 0;
	minishell(&shell);
	return (0);
}
