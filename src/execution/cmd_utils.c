/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:07:32 by ael-gady          #+#    #+#             */
/*   Updated: 2025/03/01 16:15:04 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*    path = ft_get_path(shell->env, node->content);//todo    */
void	free_matrice(char **free_me)
{
	int	i;

	if (!free_me)
		return ;
	i = 0;
	while (free_me[i])
	{
		free(free_me[i]);
		i++;
	}
	free(free_me);
}

char	get_cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*executable;
	int		i;

	if (!paths || !cmd)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i],"/");// ft_strjoin of libft!!
		if (!tmp)
			return (NULL);
		executable = ft_strjoin(tmp, cmd);// same thing ft_strjoin of libft !
		free(tmp);
		if(!executable)
			return (NULL);
		if (!access(executable, X_OK))
			return (executable);
		free(executable);
		i++;
	}
	return (NULL);
}

char	*ft_get_path(t_env *env, char *content)
{
	char	**paths;
	char	*full_path;
	char	*cmd_path;

	if (!ft_strncmp(content, "./", 2) || !ft_strncmp(content, "/", 1))
	{
		if (!access(content, X_OK))
			return (content);
		return (NULL);
	}
	// I don't know if i need the contnent of t_env or just call getenv !!
	full_path = getenv("PATH=");
	if (!full_path)
		return (NULL);
	paths = ft_split(full_path, ':');//split of libft !!
	free(full_path);
	if (!paths)
		return (NULL);
	cmd_path = get_cmd_path(paths, content);//todo
	free(paths);
	return (cmd_path);
}
