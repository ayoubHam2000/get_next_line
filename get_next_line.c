/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:02:15 by aben-ham          #+#    #+#             */
/*   Updated: 2021/11/28 15:48:02 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char		buffer[BUFFER_SIZE];
	static size_t	pos = 0;
	ssize_t			limit;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	line = NULL;
	limit = 0;
	while (1)
	{
		if (pos == 0)
		{
			limit = read(fd, buffer, BUFFER_SIZE);
			if (limit == -1)
				return (free_line(line));
			if (limit == 0)
				return (line);
			if (limit > 0 && limit < BUFFER_SIZE)
				buffer[limit] = 0;
		}
		line = mline(line, buffer, &pos);
		if (is_ended(&line, buffer, &pos))
			return (line);
	}
}
