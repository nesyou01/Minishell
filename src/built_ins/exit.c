/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:59:28 by ael-gady          #+#    #+#             */
/*   Updated: 2025/04/13 12:15:29 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void exit_error(char *msg, char *arg, int use_arg)
{
	const char *prefix = "minishell: exit: ";
	write(2, prefix, ft_strlen(prefix));
	if (use_arg && arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

long long	ft_atoll(char *digit)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	sign = 1;
	if (digit[i] && (digit[i] == '-' || digit[i] == '+'))
	{
		if (digit [i] == '-')
			sign = -1;
		i++;
	}
	res = 0;
	while (digit[i] && ft_isdigit(digit[i]))
	{
		res = res * 10 + (digit[i] - '0');
		i++;
	}
	return (res * sign);
}

static int	is_numeric(const char *str)
{
	int i = 0;

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

int	ft_builtin_exit(t_shell *shell, t_node *node, t_command *cmd)
{
	long long exit_code;

	if (!cmd->argv[1])
		ft_exit(shell, node, exit_status(0, 0));

	if (!is_numeric(cmd->argv[1]))
	{
		exit_error("numeric argument required", cmd->argv[1], 1);
		ft_exit(shell, node, 255);
	}
	exit_code = ft_atoll(cmd->argv[1]);
	if ((exit_code > LLONG_MAX) || (exit_code < LLONG_MIN))
	{
		exit_error("numeric argument required", cmd->argv[1], 1);
		ft_exit(shell, node, 255);
	}
	if (cmd->argv[2])
	{
		exit_error("too many arguments", NULL, 0);
		return (1);
	}
	ft_exit(shell, node, (unsigned char)exit_code);
	return (0);
}
