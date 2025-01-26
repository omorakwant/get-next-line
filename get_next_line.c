/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 09:31:05 by odahriz           #+#    #+#             */
/*   Updated: 2025/01/26 09:36:42 by odahriz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*last_line(char **sv)
{
	char	*last;

	last = malloc(ft_strlen(*sv) + 1);
	if (!last)
		return (free(last), NULL);
	ft_strlcpy(last, *sv, ft_strlen(*sv) + 1);
	free(*sv);
	*sv = NULL;
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

	tmp = malloc(BUFFER_SIZE + 1);
	i = read(fd, tmp, BUFFER_SIZE);
	if (i == -1 || i == 0)
	{
		free(tmp);
		return (i);
	}
	tmp[i] = '\0';
	new_line = ft_substr(*line, 0, (ft_strlen(*line)));
	free(*line);
	ft_strlcat(new_line, tmp, ft_strlen(tmp));
	*line = new_line;
	free(tmp);
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*line;
	ssize_t		i;

	i = 0;
	if (!line)
	{
		line = malloc(1);
		line[0] = '\0';
	}
	while (1)
	{
		if (ft_strchr(line, '\n'))
			return (return_line(&line));
		else if (!ft_strchr(line, '\n'))
			i = read_line(fd, &line);
		if (i <= 0)
		{
			if (i == -1 || i == 0)
				return (NULL);
			else if (*line)
				return (last_line(&line));
			break ;
		}
	}
	return (free(line), NULL);
}

int	main(void)
{
	int		fd;	
	char	*line;

	fd = open("text.txt", O_CREAT | O_RDWR, 0777);
	while (line= get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
	free(line);
	// printf("%s",line = get_next_line(fd));
	// free(line);
	// 	printf("%s",line = get_next_line(fd));
	// free(line);
}
