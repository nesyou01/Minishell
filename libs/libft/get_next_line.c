/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:06:49 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/18 15:23:51 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*holder;
	char		*result;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	result = ft_read_next_line(fd, &holder);
	if (!result && holder)
	{
		free(holder);
		holder = NULL;
	}
	return (result);
}

char	*ft_read_next_line(int fd, char **holder)
{
	ssize_t		read_bytes;
	char		*buffer;

	buffer = (char *) malloc((((size_t) BUFFER_SIZE) + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (1)
	{
		if (ft_strchr(*holder, '\n'))
			break ;
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buffer[read_bytes] = '\0';
		*holder = ft_strjoin_line(*holder, buffer, read_bytes);
		if (!*holder)
			return (free(buffer), NULL);
	}
	free(buffer);
	if (read_bytes < 0)
		return (NULL);
	return (ft_get_line(holder));
}

char	*ft_get_line(char **holder)
{
	char	*result;
	char	*nl;
	size_t	size;
	size_t	i;

	i = 0;
	nl = ft_strdup_line(ft_strchr(*holder, '\n'));
	if (!nl)
	{
		result = *holder;
		*holder = NULL;
		return (result);
	}
	size = ft_strlen(*holder) - ft_strlen(nl) + 1;
	result = (char *) malloc(size + 1);
	if (!result)
		return (free(nl), NULL);
	while (i++ < size)
		result[i - 1] = (*holder)[i - 1];
	result[i - 1] = '\0';
	free(*holder);
	*holder = ft_strdup_line(nl + 1);
	free(nl);
	return (result);
}
