/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:34:32 by aben-ham          #+#    #+#             */
/*   Updated: 2021/11/28 17:24:57 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
//#define BUFFER_SIZE 10000000

# include <unistd.h>
# include <stdlib.h>
/* max open files per process - todo, make a config option? */
# define OPEN_MAX 10240

char	*mline(char *line, char *str, size_t *pos);
char	*get_next_line(int fd);

#endif