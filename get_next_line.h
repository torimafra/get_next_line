/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:53:33 by vimafra-          #+#    #+#             */
/*   Updated: 2024/12/07 15:28:09 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef     GET_NEXT_LINE_H
# define    GET_NEXT_LINE_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stddef.h>

#ifndef		BUFFER_SIZE
# define    BUFFER_SIZE 1
#endif

int	ft_strlen(char *str);
int line_checker(char *s);
char *ft_strjoin(char *a, char *b);
void ft_strcpy(char *src, char *dest, int type);
char **ft_split(char *str);
char *get_next_line(int fd);

#endif