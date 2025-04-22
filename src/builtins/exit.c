/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:59:28 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/22 08:43:12 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_str_to_ll(char *str, long long *result)
{
	int			sign;
	long long	res;
	long long	tmp;
	int			i;

	*result = 0;
	res = 0;
	tmp = 0;
	sign = 1;
	i = 0;
	if (str[0] == '-' && ft_strcmp(str, "-9223372036854775808") == 0)
	{
		*result = LLONG_MIN;
		return (1);
	}
	if (str[i] == '+' || str[i] == '-')
		sign = 44 - str[i++];
	while (str[i] && ft_isdigit(str[i]))
	{
		tmp = res * 10 + (str[i++] - '0');
		if (tmp < res)
			return (0);
		res = tmp;
	}
	return (*result = res * sign, 1);
}

static void	ft_close_exit(t_shell *shell, t_node *node, int *fd, int status)
{
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	ft_exit(shell, node, status);
}

int	ft_builtin_exit(t_shell *shell, t_node *node, t_command *cmd, int *fd)
{
	long long	exit_code;

	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", fd[1]);
	if (!cmd->argv[1])
		ft_close_exit(shell, node, fd, exit_status(0, 0));
	if (!is_numeric(cmd->argv[1]) || !ft_str_to_ll(cmd->argv[1], &exit_code))
	{
		ft_perror3("exit", cmd->argv[1], "numeric argument required");
		ft_close_exit(shell, node, fd, 255);
	}
	if (cmd->argv[2])
	{
		ft_perror2("exit", "too many arguments");
		return (1);
	}
	ft_close_exit(shell, node, fd, exit_code % 256);
	return (0);
}
