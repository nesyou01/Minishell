/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:35:32 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/01 22:30:33 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	minishell(t_shell *shell)
{
	char			*str;
	t_node			*node;

	while (!shell->exit)
	{
		str = readline("\033[32mminishell >> \033[0m");
		if (!str)
			break ;
		ft_add_cmd_garbage(shell, str);
		node = ft_parser(shell, str);
		if (node)
			ft_execute(shell, node);
		ft_clean_cmd(shell);
	}
	ft_clean_all(shell);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void) argv;
	if (argc != 1)
		return (ft_perror("usage => ./minishell"), 1);
	env_init(&shell, env);
	shell.exit = 0;
	minishell(&shell);
	return (0);
}
