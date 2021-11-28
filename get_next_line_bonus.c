/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:30:09 by aben-ham          #+#    #+#             */
/*   Updated: 2021/11/28 17:28:17 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*free_line(char *line)
{
	free(line);
	return (NULL);
}

static short	is_ended(char **line, char *buffer, size_t *pos)
{
	if (*line == NULL)
	{
		*line = free_line(*line);
		return (1);
	}
	if ((*pos < BUFFER_SIZE && !buffer[*pos]) || buffer[*pos - 1] == '\n')
	{
		if (*pos < BUFFER_SIZE && !buffer[*pos])
			*pos = 0;
		*pos = *pos % BUFFER_SIZE;
		return (1);
	}
	*pos = *pos % BUFFER_SIZE;
	return (0);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		buffer[OPEN_MAX][BUFFER_SIZE];
	static size_t	pos[OPEN_MAX] = {0};
	ssize_t			limit;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	line = NULL;
	limit = 0;
	while (1)
	{
		if (pos[fd] == 0)
		{
			limit = read(fd, buffer[fd], BUFFER_SIZE);
			if (limit == -1)
				return (free_line(line));
			if (limit == 0)
				return (line);
			if (limit > 0 && limit < BUFFER_SIZE)
				buffer[fd][limit] = 0;
		}
		line = mline(line, buffer[fd], &(pos[fd]));
		if (is_ended(&line, buffer[fd], &(pos[fd])))
			return (line);
	}
}
