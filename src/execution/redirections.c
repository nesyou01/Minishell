/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:56:46 by ael-gady          #+#    #+#             */
/*   Updated: 2025/03/06 00:19:18 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_input_redirections(t_file *in)
{
	int fd;

	if (!in || !in->path)
		return ;
	if (in->fd != -1)
		fd = in->fd;
	else
		fd = open(in->path, O_RDONLY);
	if (fd == -1)
		ft_error("open failed !");
	if (dup2(fd, STDIN_FILENO) == -1)
		(close(fd), ft_perror("dup2 input failed !"));
	close(fd);
}

void	handle_output_redirections(t_file *out)
{
	int	fd;
	int	flags;

	if (!out || !out->path)
		return ;
	// i need maybe a flag to check the type of redirection!
	if (out->type_out_redirect == OUT_APPEND_REDIRECTER)
		flags = (O_WRONLY | O_CREAT | O_APPEND);//Append
	else if (out->type_out_redirect == OUT_REDIRECTER)//Overwrite file
		flags = (O_WRONLY | O_CREAT | O_TRUNC);
	// after solve problem of type, open file with flag!
	fd = open(out->path, flags, 0644);// behavior of bash set files permission (rw-r--r--)
	if (fd == -1)
		ft_error("open output failed !");
	if (dup2(fd, STDOUT_FILENO) == -1)
		(close(fd), ft_error("failed dup2 output !"));
	close(fd);
}
