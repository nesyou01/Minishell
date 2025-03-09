/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:34:26 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/09 23:51:09 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_perror(char *msg)
{
	char	*error;

	if (msg && *msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	ft_perror2(char *msg, char *end)
{
	char	*error;

	if (msg && *msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (end)
		ft_putstr_fd(end, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_error(char *msg)//void	ft_error(t_shell *shell, char *msg)
{
	perror(msg);
	exit(1);
}
