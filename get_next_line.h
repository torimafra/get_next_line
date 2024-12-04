/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:53:33 by vimafra-          #+#    #+#             */
/*   Updated: 2024/11/27 18:25:06 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef     GET_NEXT_LINE_H
# define    GET_NEXT_LINE_H
#endif

#ifndef		BUFFER_SIZE
# define    BUFFER_SIZE 5

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(char *content);
//void	ft_lstadd_back(t_list *lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int	ft_lstsize(t_list *lst);
int	ft_strlen(char *str);
int	find_eol(char *s);
char    *substr(char *s, unsigned int end);
int line_checker(char *s);
char *get_next_line(int fd);

#endif