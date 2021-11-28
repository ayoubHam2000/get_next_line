/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 22:43:08 by aben-ham          #+#    #+#             */
/*   Updated: 2021/11/28 22:50:34 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*freeline(char *line)
{
	free(line);
	return (NULL);
}

static int	shift_if_break(char *buffer)
{
	int	i;
	int	j;
	int	f;

	i = 0;
	j = 0;
	f = 0;
	while (i < BUFFER_SIZE && buffer[i] != '\n' && buffer[i] != 0)
		i++;
	if (buffer[i] == '\n')
		f = 1;
	if (i == BUFFER_SIZE)
		return (f);
	i++;
	while (i < BUFFER_SIZE && buffer[i])
		buffer[j++] = buffer[i];
	buffer[j] = 0;
	return (f);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		buffer[OPEN_MAX][BUFFER_SIZE];
	ssize_t			nbread;

	line = NULL;
	while (1)
	{
		if (!buffer[fd][0])
		{
			nbread = read(fd, buffer[fd], BUFFER_SIZE);
			if (nbread == -1)
				return (freeline(line));
			if (nbread == 0)
				return (line);
			if (nbread > 0 && nbread < BUFFER_SIZE)
				buffer[fd][nbread] = 0;
		}
		line = mline(line, buffer[fd]);
		if (!line)
			return (NULL);
		if (shift_if_break(buffer[fd]))
			return (line);
		buffer[fd][0] = 0;
	}
}
