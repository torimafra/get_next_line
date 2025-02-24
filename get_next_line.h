/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:53:33 by vimafra-          #+#    #+#             */
/*   Updated: 2025/01/04 17:38:28 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h> //printf
# include <unistd.h> //open()
# include <fcntl.h> //O_RDONLY
# include <stdlib.h> //malloc()
# include <stddef.h> //size_t

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		strcounter(char *str, char c);
int		ft_split(char **str, char **result, char **cache);
int		line_checker(char **str, char **result, char **cache);
int		line_checker(char **str, char **result, char **cache);
void	strchrcopy(char *src, char *dest, char c, int type);
char	*ft_strdup(char *s);
char	*ft_strjoin(char **a, char *b);
char	*create_buffer(int fd);
char	*buffer_handler(int fd, char **result, char **cache);
char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
