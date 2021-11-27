/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:02:15 by aben-ham          #+#    #+#             */
/*   Updated: 2021/11/27 22:27:05 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#define BUFFER_SIZE 10

static int	len(char *b, size_t rp, ssize_t limit, short *flag)
{
	int	i;

	i = rp % BUFFER_SIZE;
	*flag = 0;
	while (i < limit && b[i] != '\n')
		i++;
	if (i < limit && b[i] == '\n')
	{
		i++;
		if (i == limit && limit < BUFFER_SIZE)
			*flag = -2;
		else
			*flag = -1;
	}
	else if (i == limit && limit < BUFFER_SIZE)
		*flag = -2;
	return (i - (rp % BUFFER_SIZE));
}

static char	*getl(char *line, char *b, size_t ltr, size_t *readpos)
{
	char	*new_line;
	size_t	len_line;
	size_t	i;

	len_line = 0;
	while (line && line[len_line] != 0)
		len_line++;
	len_line = len_line + ltr;
	new_line = malloc(len_line + 1);
	if (new_line == NULL)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (line && line[i] != 0)
	{
		new_line[i] = line[i];
		i++;
	}
	free(line);
	while (i < len_line)
		new_line[i++] = b[((*readpos)++ % BUFFER_SIZE)];
	new_line[len_line] = 0;
	return (new_line);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		buffer[BUFFER_SIZE];
	static size_t	readpos = 0;
	static ssize_t	limit = 0;
	short			flag;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	while (1)
	{
		if (limit == -1)
			break ;
		if (limit == 0)
			return (line);
		line = getl(line, buffer, len(buffer, readpos, limit, &flag), &readpos);
		if (flag == -2)
			readpos = 0;
		if (flag == -1 || flag == -2)
			return (line);
	}
	free(line);
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main()
{
	int fileDis = open("../bin/test", O_RDONLY);
	char *p;

	while ((p = get_next_line(fileDis)))
		printf("%s", p);
	close(fileDis);
	return (0);
}
*/
