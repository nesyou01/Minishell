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
	t_token		*token;
	t_node		*node;

	while (!shell->exit)
	{
		str = readline("\033[32mminishell >> \033[0m");
		token = ft_parser(shell, str);
		if (!syntax_validator(token))
		{
			node = ft_tokens_to_nodes(shell, token);
			ft_node_parser(shell, &node);
			// ft_to_tree(node);
			while (node)
			{
				// if (node->in)
					// printf("<< %s", node->in->path);
				printf(" %s ", node->content);
				// if (node->out)
				// 	printf(">> %s", node->out->path);
				printf("\n");
				node = node->next;
			}
		}
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
