/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:34:26 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/13 19:24:26 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_perror(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(msg, 2);
}

void	ft_perror2(char *msg, char *end)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(end, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_perror3(char *first, char *middle, char *end)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(first, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(middle, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(end, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_error(t_shell *shell, t_node *node, char *msg, int status)
{
	perror(msg);
	ft_exit(shell, node, status);
}
