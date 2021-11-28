/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:02:15 by aben-ham          #+#    #+#             */
/*   Updated: 2021/11/28 21:50:23 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *freeline(char *line)
{
	free(line);
	return (NULL);
}

static char	*strbreakl(char *line)
{
	while (*line != '\n' && *line != 0)
		line++;
	if (*line == '\n')
		return line;
	return (NULL);
}

static void	shift(char *buffer)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && i < BUFFER_SIZE)
		i++;
	if (i == BUFFER_SIZE)
		buffer[0] = 0;
	i++;
	while (i < BUFFER_SIZE && buffer[i])
	{
		buffer[j] = buffer[i];
		j++;
		i++;
	}
	buffer[j] = 0;
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		buffer[BUFFER_SIZE];
	ssize_t			nbread;

	line = NULL;
	while (1)
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
		if (strbreakl(line))
		{
			shift(buffer);
			return (line);
		}
		buffer[0] = 0;
	}
}

#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd;
	char *p;

	fd = open("../bin/test1", O_RDONLY);
	while ((p = get_next_line(fd)))
	{
		printf("%s", p);	
	}
	return (0);
}
