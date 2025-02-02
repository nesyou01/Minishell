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
	int			error;

	error = 0;
	token = NULL;
	node = NULL;
	while (!shell->exit)
	{
		node = NULL;
		str = readline("\033[32mminishell >> \033[0m");
		ft_parser(shell, str, &token);
		error = syntax_validator(token);
		// if (!error)
		// 	error = ft_node_parser(&node, token);
		if (!error)
		{
			while (token)
			{
				printf("--> %s --> %d\n", token->content, token->type);
				token = token->next;
			}
		}
		// ft_to_tree(node);
		// while (node)
		// {
		// 	// printf("%s\n",  node->content);
		// 	if (node->type >= 100)
		// 		printf("%s <-%s -> %s\n", node->l_node->content, node->content, node->r_node->content);
		// 	// else
		// 	// 	printf("%s\n", node->content);
		// 	node = node->next;
		// }
		
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
