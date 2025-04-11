/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 07:05:33 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/11 20:06:22 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(t_file *io)
{
	int	fd;
	int	flags;

	flags = 0;
	if (io->is_ambiguous)
		return (ft_perror("ambiguous redirect"), -1);
	if (io->type == OUT_APPEND_REDIRECTER)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else if (io->type == OUT_REDIRECTER)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (io->type == IN_REDIRECTER)
		flags = O_RDONLY;
	fd = open(io->path, flags, 0644);
	io->fd = fd;
	if (fd == -1)
		ft_perror3("minishell", io->path, strerror(errno));
	return (fd);
}

int	redirect_fd(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		close(old_fd);
		ft_perror("dup2 failed");
		return (0);
	}
	close(old_fd);
	return (1);
}

int	handle_redirections(t_file *io)
{
	int	fd;

	while (io)
	{
		if (io->fd == -1)
			fd = open_file(io);
		else
			fd = io->fd;
		if (fd == -1)
			return (0);
		if ((io->type == IN_REDIRECTER && !redirect_fd(fd, STDIN_FILENO))
			|| ((io->type == OUT_REDIRECTER || io->type == OUT_APPEND_REDIRECTER)
				&& !redirect_fd(fd, STDOUT_FILENO)))
			return (0);
		io = io->next;
	}
	return (1);
}
