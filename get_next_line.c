/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:02:15 by aben-ham          #+#    #+#             */
/*   Updated: 2021/11/29 12:21:00 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if (buffer[i] != 0)
		i++;
	while (i < BUFFER_SIZE && buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = 0;
	return (f);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		buffer[BUFFER_SIZE];
	ssize_t			nbread;

	line = NULL;
	while (fd >= 0)
	{
		if (!buffer[0])
		{
			nbread = read(fd, buffer, BUFFER_SIZE);
			if (nbread == -1)
				return (freeline(line));
			if (nbread == 0)
				return (line);
			if (nbread > 0 && nbread < BUFFER_SIZE)
				buffer[nbread] = 0;
		}
		line = mline(line, buffer);
		if (!line)
			return (NULL);
		if (shift_if_break(buffer))
			return (line);
		buffer[0] = 0;
	}
	return (NULL);
}
