/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:11:18 by ylagmah           #+#    #+#             */
/*   Updated: 2025/01/30 12:34:03 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_parser(t_shell *shell, char *str)
{
	t_token	*token;

	token = ft_split_tokens(shell, str);
	ft_tokenize(token);
	ft_merge_tokens(shell, &token);
	ft_merge_args_with_cmd(shell, token);
	return (token);
}
