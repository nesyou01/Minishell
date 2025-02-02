/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:27:27 by ylagmah           #+#    #+#             */
/*   Updated: 2024/11/03 18:11:35 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isscpace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	ft_return(int sign)
{
	if (sign == -1)
		return (0);
	return (-1);
}

int	ft_atoi(const char	*str)
{
	int			i;
	long		result;
	int			sign;

	sign = 1;
	result = 0;
	i = 0;
	while (ft_isscpace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - 48);
		if ((result * 10 + (str[i] - 48) < 0) || result < 0)
			return (ft_return(sign));
		i++;
	}
	return (result * sign);
}
