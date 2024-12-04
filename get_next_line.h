/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:53:33 by vimafra-          #+#    #+#             */
/*   Updated: 2024/12/04 16:41:18 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef     GET_NEXT_LINE_H
# define    GET_NEXT_LINE_H
#endif

#ifndef		BUFFER_SIZE
# define    BUFFER_SIZE 3

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int	ft_strlen(char *str);
char *ft_strjoin(char *a, char *b);
int	find_eol(char *s);
//char    *substr(char *s, unsigned int end);
int line_checker(char *s);
char *get_next_line(int fd);
void set_null(char *str);
char **ft_split(char *str);

#endif