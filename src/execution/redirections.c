#include "../../includes/minishell.h"

int	open_file(t_file *io)
{
	int	fd;
	int	flags;

	flags = 0;
	if (io->type == OUT_APPEND_REDIRECTER)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else if (io->type == OUT_REDIRECTER)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (io->type == IN_REDIRECTER)
		flags = O_RDONLY;
	fd = open(io->path, flags, 0644);
	if (fd == -1)
		ft_perror(io->path);
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

// void	restore_tty_fds(int *tty_fd)
// {
// 	if (dup2(tty_fd[0], STDIN_FILENO) == -1)
// 	{
// 		(close(tty_fd[0]), close(tty_fd[1]), close(tty_fd[2]));
// 		ft_perror("failed to restore tty fd !");
// 		return ;
// 	}
// 	if (dup2(tty_fd[1], STDOUT_FILENO) == -1)
// 	{
// 		(close(tty_fd[0]), close(tty_fd[1]), close(tty_fd[2]));
// 		ft_perror("failed to restore tty fd !");
// 		return ;
// 	}
// 	if (dup2(tty_fd[2], STDERR_FILENO) == -1)
// 	{
// 		(close(tty_fd[0]), close(tty_fd[1]), close(tty_fd[2]));
// 		ft_perror("failed to restore tty fd !");
// 		return ;
// 	}
// 	close(tty_fd[0]);
// 	close(tty_fd[1]);
// 	close(tty_fd[2]);
// }

// int	save_tty_fds(int *tty_fd)
// {
// 	tty_fd[0] = dup(0);
// 	if (tty_fd[0] == -1)
// 		return (ft_perror("failed to save tty fd !"), 0);
// 	tty_fd[1] = dup(1);
// 	if (tty_fd[1] == -1)
// 	{
// 		close(tty_fd[0]);
// 		ft_perror("failed to save tty fd !");
// 		return(0);
// 	}
// 	tty_fd[2] = dup(2);
// 	if (tty_fd[2] == -1)
// 	{
// 		(close(tty_fd[0]), close(tty_fd[1]));
// 		ft_perror("failed to save tty fd !");
// 		return(0);
// 	}
// 	return (1);
// }

// int	handle_redirections(t_file *io)
// {
// 	int	fd;
// 	int	tty_fd[3];

// 	if (!save_tty_fds(tty_fd))
// 		return (0);
// 	while (io)
// 	{
// 		fd = open_file(io);
// 		if (fd == -1)
// 			return (restore_tty_fds(tty_fd), 0);
// 		if (io->type == IN_REDIRECTER && !redirect_fd(fd, STDIN_FILENO))
// 			return (restore_tty_fds(tty_fd), 0);
// 		else if((io->type == OUT_REDIRECTER || io->type == OUT_APPEND_REDIRECTER)
// 			&& !redirect_fd(fd, STDOUT_FILENO))
// 			return (restore_tty_fds(tty_fd), 0);
// 		io = io->next;
// 	}
// 	restore_tty_fds(tty_fd);
// 	return (1);
// }

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
