/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:56:46 by ael-gady          #+#    #+#             */
/*   Updated: 2025/03/06 23:29:30 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	handle_input_redirections(t_file *in)//bash-3.2$  ls > out33 > out44
// {
// 	int fd;

// 	if (!in || !in->path)
// 		return ;
// 	if (in->fd != -1)
// 		fd = in->fd;
// 	else
// 		fd = open(in->path, O_RDONLY);
// 	if (fd == -1)
// 		ft_error("open failed !");
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 		(close(fd), ft_perror("dup2 input failed !"));
// 	close(fd);
// }

// void	handle_output_redirections(t_file *out)//fix 
// {
// 	int	fd;
// 	int	flags;

// 	if (!out)
// 		return ;
// 	// i need maybe a flag to check the type of redirection!
// 	if (out->type_out_redirect == OUT_APPEND_REDIRECTER)
// 		flags = (O_WRONLY | O_CREAT | O_APPEND);//Append
// 	else if (out->type_out_redirect == OUT_REDIRECTER)//Overwrite file
// 		flags = (O_WRONLY | O_CREAT | O_TRUNC);
// 	// after solve problem of type, open file with flag!
// 	fd = open(out->path, flags, 0644);// behavior of bash set files permission (rw-r--r--)
// 	if (fd == -1)
// 		ft_error("open output failed !");
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 		(close(fd), ft_error("failed dup2 output !"));
// 	close(fd);
// }

static void	ft_perror(const char *msg)
{
	if (msg && *msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
	}
	if (errno != 0)
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

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

int	handle_redirections(t_file *io)
{
	int	fd;

	while (io)
	{
		fd = open_file(io);
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
