/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:07:32 by ael-gady          #+#    #+#             */
/*   Updated: 2025/03/04 13:46:43 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


//------------------

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static size_t	calc_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	*fill_subs(char const **s, char c)
{
	size_t	i;
	char	*subs;
	size_t	len;

	while (**s == c && **s)
		(*s)++;
	len = calc_len(*s, c);
	subs = (char *) malloc (sizeof (char) * (len + 1));
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len)
	{
		subs[i] = **s;
		i++;
		(*s)++;
	}
	subs[i] = '\0';
	return (subs);
}

static char	**free_2_dim(char **strs, size_t index)
{
	size_t	i;

	i = 0;
	while (i < index)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split_(char const *s, char c)
{
	size_t	words;
	char	**strs;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	words = count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	while (i < words)
	{
		strs[i] = fill_subs(&s, c);
		if (!strs[i])
			return (free_2_dim(strs, i));
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

//-------------------


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

char	*get_cmd_path(t_shell *shell, char **paths, char *cmd)
{
	char	*tmp;
	char	*executable;
	int		i;

	if (!paths || !cmd)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(shell, paths[i], "/");// ft_strjoin of libft!!
		if (!tmp)
			return (NULL);
		executable = ft_strjoin(shell, tmp, cmd);// same thing ft_strjoin of libft !
		// free(tmp);
		if(!executable)
			return (NULL);
		if (!access(executable, X_OK))
			return (executable);
		// free(executable);
		i++;
	}
	return (NULL);
}

char	*ft_get_path(t_shell *shell, t_env *env, char *content)
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
	full_path = getenv("PATH=");//create a function based by t_env !!
	if (!full_path)
		return (NULL);
	paths = ft_split_(full_path, ':');//split of libft !!
	// free(full_path);
	if (!paths)
		return (NULL);
	cmd_path = get_cmd_path(shell, paths, content);//todo
	free_matrice(paths);
	return (cmd_path);
}
