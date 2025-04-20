/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:20:44 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/20 06:33:34 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_status(int action, int value)
{
	static int	status = 0;

	if (action == 0)
		return (status);
	else if (action == 1)
		status = value;
	return (status);
}
int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}
