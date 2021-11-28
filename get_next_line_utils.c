/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:02:13 by aben-ham          #+#    #+#             */
/*   Updated: 2021/11/28 15:40:34 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	lentcpy(char *buffer, size_t pos)
{
	size_t	i;

	i = pos;
	while (buffer[i] != '\n' && buffer[i] != 0 && i < BUFFER_SIZE)
		i++;
	if (buffer[i] == '\n')
		i++;
	return (i - pos);
}

char	*mline(char *line, char *str, size_t *pos)
{
	char	*new_line;
	size_t	len_line;
	size_t	i;

	len_line = 0;
	i = 0;
	while (line && line[len_line] != 0)
		len_line++;
	len_line = len_line + lentcpy(str, *pos);
	new_line = malloc(len_line + 1);
	if (!new_line)
		return (NULL);
	while (line && *line)
		new_line[i++] = *line++;
	free((line - i));
	while (i < len_line)
		new_line[i++] = str[(*pos)++];
	new_line[len_line] = 0;
	return (new_line);
}
