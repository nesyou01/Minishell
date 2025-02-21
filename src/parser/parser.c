/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:11:18 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/21 11:45:08 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_execute	*ft_parser(t_shell *shell, char *str)
{
	t_token		*token;
	t_execute	*exe;

	exe = ft_malloc(shell, sizeof(t_execute));
	exe->in = NULL;
	exe->out = NULL;
	exe->here_doc = NULL;
	exe->node = NULL;
	token = ft_split_tokens(shell, str);
	ft_tokenize(token);
	ft_merge_tokens(shell, &token);
	ft_merge_args_with_cmd(shell, token);
	if (syntax_validator(token))
		return (NULL);
	ft_tokens_to_nodes(shell, token, exe);
	ft_tree_builder(shell, &(exe->node));
	return (exe);
}
