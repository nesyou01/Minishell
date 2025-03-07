/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:34:26 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/07 00:04:50 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_perror(char *msg)
{
	char	*error;

	if (msg && *msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (errno != 0)
	{
		error = strerror(errno);
		if (error)
			ft_putstr_fd(error, 2);
		//free(error);
	}
	ft_putstr_fd("\n", 2);
}
