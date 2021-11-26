/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:02:15 by aben-ham          #+#    #+#             */
/*   Updated: 2021/11/26 23:10:02 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
error : read = -1
malloc = null
*/

#include "get_next_line.h"

static size_t	count_until_eol_or_eob(char *buffer, size_t *pos, size_t max)
{
	size_t	i;

	i = 0;
	while (buffer[i + *pos] != '\n' && *pos != BUFFER_SIZE)
	{
		(*pos)++;
		i++;
	}
	if (*pos == BUFFER_SIZE)
		*pos = 0;
	return (i);
}

static char	*copy_to_line(char *line, char *buffer, size_t *start, size_t end)
{
	char	*newLine;
	size_t	len_line;
	size_t	i;
	
	i = 0;
	len_line = 0;
	while (line && line[len_line] != 0)
		len_line++;
	len_line = len_line + (end - *start + 2);
	newLine = malloc(len_line + 1);
	while (line && line[i] != 0)
		newLine[i++] = line[i];
	while (i < len_line)
		newLine[i++] = buffer[(*start)++];
	if (*start == BUFFER_SIZE)
		*start = 0;
	free(line);
	return (newLine);
}

//copy to line until the end of buffer or encounter \n
static char	*copy_to_line(char *line, char *buffer, size_t *pos, size_t max)
{
	char	*newLine;
	size_t	len_line;
	size_t	len_buffer;
	size_t	i;

	
	len_line = 0;
	while (line && line[len_line] != 0)
		len_line++;
	len_buffer = count_until_eol_or_eob(buffer, pos);
	newLine = malloc(len_line + len_buffer + 1);
	i = 0;
	while (line && line[i] != 0)
	{
		newLine[i] = line[i];
		i++;
	}
	while (i < len_line + len_buffer)
	{
		newLine[i] = buffer[i - len_line];
		i++;
	}
	free(line);
	return (newLine);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		buffer[BUFFER_SIZE];
	static size_t	readpos = 0;
	size_t			count;

	line = NULL;
	if (readpos != 0)
		
	while (1)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == 0)
			break;
		if (count < BUFFER_SIZE)
			break;
		line = copy_to_line(line, buffer, &readpos);
	}
	return (line);
}


#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main()
{
	int fileDis = open("../bin/test", O_RDONLY);
	char *p;

	p = get_next_line(fileDis);
	printf("%s", p);
	close(fileDis);
	return (0);
}

