/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:27:00 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/22 02:44:00 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*join_all(t_shell *shell, char *s1, t_env *env, int trim)
{
	char	*result;

	if (env)
	{
		if (trim)
			result = ft_strjoin(shell, s1, ft_trim_var(shell, env->value));
		else
			result = ft_strjoin(shell, s1, env->value);
	}
	else
		result = s1;
	return (result);
}

static char	*join_status_code(t_shell *shell, char *start, char *end)
{
	return (ft_strjoin(shell, ft_strjoin(shell,
				start, ft_itoa(shell, exit_status(0, 0))), end));
}

static char	*expand_var(t_shell *shell, char *str, char *sign, int trim)
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
	return (ft_strjoin(shell, join_all(shell, start, env, trim), end));
}

char	*ft_expand_all_vars(t_shell *shell,	char *str, int trim)
{
	char			*sign;

	sign = str;
	while (sign)
	{
		sign = ft_strchr(sign, '$');
		if (!sign)
			return (str);
		if ((!sign[1] && trim) || sign[1] == '?'
			|| (!ft_isdigit(sign[1]) && ft_isvalid_var(sign[1])))
		{
			str = expand_var(shell, str, sign, trim);
			sign = str;
		}
		else
			sign++;
	}
	return (str);
}
