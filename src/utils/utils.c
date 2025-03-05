/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:34:26 by ylagmah           #+#    #+#             */
/*   Updated: 2025/03/05 20:58:14 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_perror(char *str)
{
	ft_putstr_fd("\033[91mError: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	else
		ft_putstr_fd("Somthing went wrong", 2);
	ft_putstr_fd("\033[91m\n", 2);
}
