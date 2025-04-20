/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 07:05:33 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/21 00:08:22 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_files(t_file *io)
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
		ft_perror2(io->path, strerror(errno));
	return (fd);
}

static int	redirect_fd(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		return (ft_perror("dup2 failed"), 0);
	return (1);
}

static int	handle_here_doc(t_shell *shell, t_file *io)
{
	int		fds[2];
	char	*line;
	char	*tmp;

	if (!io->expand)
		return (io->fd);
	if (ft_pipe(fds, "/tmp/.mini_tmp"))
		return (-1);
	while (1)
	{
		line = get_next_line(io->fd);
		if (!line)
			break ;
		tmp = ft_expand_all_vars(shell, line);
		ft_putstr_fd(tmp, fds[1]);
		free(line);
	}
	close(io->fd);
	close(fds[1]);
	io->fd = fds[0];
	return (io->fd);
}

int	handle_redirections(t_shell *shell, t_file *io)
{
	int	fd;

	while (io)
	{
		if (io->fd == -1)
			fd = open_files(io);
		else
			fd = handle_here_doc(shell, io);
		if (fd == -1)
			return (0);
		if ((io->type == IN_REDIRECTER && !redirect_fd(fd, STDIN_FILENO))
			|| ((io->type == OUT_REDIRECTER
					|| io->type == OUT_APPEND_REDIRECTER)
				&& !redirect_fd(fd, STDOUT_FILENO)))
			return (0);
		io = io->next;
	}
	return (1);
}
