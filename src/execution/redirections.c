/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:56:46 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/26 11:08:15 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_input_redirections(t_file *in)
{
	int fd;

	if (!in || !in->path)
		return ;
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

	if (!out || out->path)
		return ;
	// i need maybe a flag for check the type of redirection!
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

void	handle_here_doc(t_file *heredoc)
{
	int		fd_tmp;
	char	*line;

	if (!heredoc || !heredoc->path)
		return ;
	fd_tmp = open("/tmp/.heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_tmp == -1)
		ft_error("failed open heredoc_tmp");
	heredoc->fd = open("/tmp/.heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (heredoc->fd == -1)
		ft_error("failed open heredoc_tmp");
	// remove /tmp/.heredoc_tmp but we can work with him when my process in life!
	unlink("/tmp/.heredoc_tmp");
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break;
		//here_doc->path in this case take the limiter in content !
		if (ft_strcmp(line, heredoc->path)
			&& line[ft_strlen(heredoc->path)] == '\n')
		{
			free(line);
			break;
		}
		(write(fd_tmp, line, ft_strlen(line)), free(line));
	}
	close(fd_tmp);
	if (dup2(heredoc->fd, STDIN_FILENO) == -1)
		(close(heredoc->fd), ft_error("failed dup2 input !"));
	// close(heredoc->fd); //we needed open !
	
}
