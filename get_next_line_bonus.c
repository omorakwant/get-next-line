/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 09:31:05 by odahriz           #+#    #+#             */
/*   Updated: 2025/01/27 00:28:49 by odahriz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*last_line(char **line)
{
	char	*last;

	last = malloc(ft_strlen(*line) + 1);
	if (!last)
		return (free(last), NULL);
	ft_strlcpy(last, *line, ft_strlen(*line) + 1);
	free(*line);
	*line = NULL;
	return (last);
}

char	*return_line(char **line)
{
	char	*tmp1;
	char	*tmp2;
	size_t	i;

	i = 0;
	while ((*line)[i] != '\n' && (*line)[i] != '\0')
		i++;
	tmp1 = ft_substr(*line, 0, i + 1);
	i++;
	tmp2 = ft_substr(*line, i, (ft_strlen(*line) - i));
	free(*line);
	*line = tmp2;
	return (tmp1);
}

ssize_t	read_line(int fd, char **line)
{
	char	*tmp;
	ssize_t	i;
	char	*new_line;
	size_t	new_size;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (free(tmp), -1);
	i = read(fd, tmp, BUFFER_SIZE);
	if (i <= 0)
		return (free(tmp), i);
	tmp[i] = '\0';
	new_size = (ft_strlen(*line) + i + 1);
	new_line = malloc(sizeof(char) * new_size);
	if (!new_line)
		return (free(new_line), -1);
	ft_strlcpy(new_line, *line, (ft_strlen(*line) + 1));
	ft_strlcat(new_line, tmp, (ft_strlen(new_line) + ft_strlen(tmp) + 1));
	free(*line);
	*line = malloc(sizeof(char) * new_size);
	ft_strlcpy(*line, new_line, new_size + 1);
	return (free(new_line), free(tmp), i);
}

char	*get_next_line(int fd)
{
	static char	*line[1024];
	ssize_t		i;

	i = 0;
	if (!line[fd] && fd >= 0)
	{
		line[fd] = malloc(1);
		line[fd][0] = '\0';
	}
	while (1)
	{
		if (ft_strchr(line[fd], '\n'))
			return (return_line(&line[fd]));
		if (!ft_strchr(line[fd], '\n'))
			i = read_line(fd, &line[fd]);
		if (i <= 0)
		{
			if (i == -1)
				return (free(line[fd]), NULL);
			if (*line[fd])
				return (last_line(&line[fd]));
			break ;
		}
	}
	return (free(line[fd]), line[fd] = NULL, NULL);
}
