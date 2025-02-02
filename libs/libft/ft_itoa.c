/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:27:55 by ylagmah           #+#    #+#             */
/*   Updated: 2024/10/30 16:07:46 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	int_len(int n)
{
	int	tmp;
	int	len;
	int	nn;

	nn = ft_abs(n);
	if (nn >= 0 && nn <= 9)
		return (1);
	tmp = nn;
	len = 0;
	while (tmp > 0)
	{
		tmp /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;
	int		len;
	int		tmp;

	len = int_len(n);
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		len++;
	result = (char *) malloc(len + 1);
	if (!result)
		return (NULL);
	tmp = ft_abs(n);
	i = 0;
	while (i < len)
	{
		result[len - 1 - i] = (tmp % 10) + 48;
		tmp /= 10;
		i++;
	}
	result[i] = '\0';
	if (n < 0)
		result[0] = '-';
	return (result);
}
