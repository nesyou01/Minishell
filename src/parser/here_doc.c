/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:56:45 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/22 02:41:24 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*remove_quotes(t_shell *shell, t_token *token)
{
	t_node	*node;

	node = ft_new_node(shell, token);
	if (node->content[0] == '$' && ft_is_quote(node->content[1]))
		node->content = ft_strdup(shell, node->content + 1);
	ft_remove_quotes(shell, node, 0);
	return (remove_empty(shell, node, 0, ft_strlen(node->content)));
}

int	ft_pipe(int fds[2], const char *path)
{
	fds[1] = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fds[1] == -1)
		return (1);
	fds[0] = open(path, O_RDONLY);
	if (fds[0] == -1)
		return (close(fds[1]), 1);
	unlink(path);
	return (0);
}

static void	convert_here_doc(t_token *token)
{
	token->prev->type = IN_REDIRECTER;
	token->type = FILE;
	token->expand = (!ft_strchr(token->content, '\'')
			&& !ft_strchr(token->content, '"'));
}

static void	read_here_doc(t_shell *shell, char *limiter, int fds[2])
{
	char	*input;

	close(fds[0]);
	signals_listener(1);
	while (1)
	{
		input = readline("here_doc> ");
		if (!input)
			break ;
		ft_add_cmd_garbage(shell, input);
		if (ft_strcmp(limiter, input) == 0)
			break ;
		ft_putstr_fd(input, fds[1]);
		ft_putstr_fd("\n", fds[1]);
	}
	close(fds[1]);
	ft_exit(shell, NULL, EXIT_SUCCESS);
}

int	here_doc_handler(t_shell *shell, t_token *token)
{
	char	*limiter;
	int		fds[2];
	pid_t	pid;
	int		status;

	if (ft_pipe(fds, "/tmp/.here_doc"))
		return (1);
	convert_here_doc(token);
	token->fd = fds[0];
	limiter = remove_quotes(shell, token);
	pid = fork();
	if (pid == -1)
		return (close(fds[1]), close(fds[0]), 1);
	if (pid == 0)
		read_here_doc(shell, limiter, fds);
	close(fds[1]);
	waitpid(pid, &status, 0);
	status = WEXITSTATUS(status);
	return (status);
}
