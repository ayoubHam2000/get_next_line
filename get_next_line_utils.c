/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:02:13 by aben-ham          #+#    #+#             */
/*   Updated: 2021/11/28 20:10:07 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	lentcpy(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != 0 && i < BUFFER_SIZE)
		i++;
	if (buffer[i] == '\n')
		i++;
	return (i);
}

char	*mline(char *line, char *str)
{
	char	*new_line;
	size_t	len_line;
	size_t	i;

	len_line = 0;
	i = 0;
	while (line && line[len_line] != 0)
		len_line++;
	len_line = len_line + lentcpy(str);
	new_line = malloc(len_line + 1);
	if (!new_line)
	{
		free(line);	
		return (NULL);
	}
	while (line && *line)
		new_line[i++] = *line++;
	free((line - i));
	while (i < len_line)
		new_line[i++] = *str++;
	new_line[len_line] = 0;
	return (new_line);
}
