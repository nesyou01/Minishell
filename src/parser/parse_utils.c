/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:15 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/13 16:27:16 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(t_token *token)
{
	return (token->type == OUT_REDIRECTER
		|| token->type == IN_REDIRECTER
		|| token->type == OUT_APPEND_REDIRECTER);
}
