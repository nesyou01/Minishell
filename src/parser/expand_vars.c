/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:00 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/15 13:13:44 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*join_all(t_shell *shell, char *s1, t_env *env, char *s3)
{
	char	*result;

	if (env)
		result = ft_strjoin(shell, s1, ft_trim_var(shell, env->value));
	else
		result = s1;
	result = ft_strjoin(shell, result, s3);
	return (result);
}

static char	*join_status_code(t_shell *shell, char *start, char *end)
{
	return (ft_strjoin(shell, ft_strjoin(shell,
				start, ft_itoa(shell, exit_status(0, 0))), end));
}

static char	*expand_var(t_shell *shell, char *str, char *sign)
{
	size_t			total;
	char			*start;
	t_env			*env;
	char			*end;
	size_t			i;

	total = ft_strlen(str);
	i = total - ft_strlen(sign);
	if (i)
		start = ft_substr(shell, str, 0, i);
	else
		start = NULL;
	i = get_var_end(sign);
	end = ft_substr(shell, sign, i + 1, ft_strlen(sign));
	if (sign[1] == '?')
		return (join_status_code(shell, start, end));
	env = ft_get_env(shell->env, ft_substr(shell, sign, 1, i));
	return (join_all(shell, start, env, end));
}

char	*ft_expand_all_vars(t_shell *shell,	char *str)
{
	char			*sign;

	sign = str;
	while (sign)
	{
		sign = ft_strchr(sign, '$');
		if (!sign)
			return (str);
		if (sign[1] == '?' || (!ft_isdigit(sign[1]) && ft_isvalid_var(sign[1])))
		{
			str = expand_var(shell, str, sign);
			sign = str;
		}
		else
			sign++;
	}
	return (str);
}
