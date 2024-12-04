/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:50:35 by vimafra-          #+#    #+#             */
/*   Updated: 2024/12/04 09:31:40 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_strdup(char *str)
{
    char    *result;
    int i;

    i = 0;
    if (!str || str[i] == '\0')
        return (NULL);
    while(str[i] != '\0')
        i++;
    result = (char *)malloc((i + 1) * sizeof(char));
    if (result == NULL)
        return (NULL);
    i = 0;
    while (str[i] != '\0')
    {
        result[i] = str[i];
        i++;
    }
    result[i] = '\0';
    return (result);
}

char *ft_strjoin(char *src, char *add)
{
    
}

t_list	*ft_lstnew(char *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
    if (content[0] == '\0' || content == NULL)
        return (NULL);
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	return (new_node);
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *last;

	if (!lst || !new)
        return ;
    if (*lst == NULL)
    {
        *lst = new;
        return ;
    }
    last = *lst;
    while(last->next)
        last = last->next;
    last->next = new;
}

char *ft_lstsize(t_list *lst)
{
    t_list *ptr;

    if (!lst)
        return ;
    ptr = lst;
    while (ptr != NULL)
    {

        ptr = ptr->next;
    }
    return ("ok");
}

// int	main(void)
// {
//     ft_strdup("teste");
// 	return (0);
// }
