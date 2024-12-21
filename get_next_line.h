/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:53:33 by vimafra-          #+#    #+#             */
/*   Updated: 2024/12/21 15:15:18 by vimafra-         ###   ########.fr       */
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

int strcounter(char *str, char c);
char	*ft_strdup(char *s);
int	line_checker(char **str, char **result, char **cache);
void	strchrcopy(char *src, char *dest, char c, int type);
char	*ft_strjoin(char *a, char *b);
int ft_split(char **str, char **result, char **cache);
char *create_buffer(int fd, char **result);
char    *buffer_handler(int fd, char **result, char **cache);
char    *get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);

#endif