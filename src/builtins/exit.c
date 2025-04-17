/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:59:28 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/17 13:37:34 by ael-gady         ###   ########.fr       */
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

static int	ft_parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

int	ft_str_to_ll(const char *str, long long *result)
{
	long long	tmp;
	int			sign;

	tmp = 0;
	*result = 0;
	if (!str || !*str)
		return (0);
	sign = ft_parse_sign(&str);
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		if ((sign == 1 && tmp > (LLONG_MAX - (*str - '0')) / 10)
			|| (sign == -1 && tmp > (-(LLONG_MIN + (*str - '0'))) / 10))
			return (0);
		tmp = tmp * 10 + (*str++ - '0');
	}
	*result = tmp * sign;
	return (1);
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
