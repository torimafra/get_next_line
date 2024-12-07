/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:59:28 by vimafra-          #+#    #+#             */
/*   Updated: 2024/12/07 14:34:12 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *copy_until_break(char *s)
{

}

char *get_next_line(int fd)
{
    char    buffer[BUFFER_SIZE];
    char    *result;
    static char    *cache = {NULL};
    char    **middle_break;
    int read_status;

    result = "";
    if (fd == -1 || BUFFER_SIZE <= 0)
        return (NULL);
    // if (cache)
    // {
    //     if (line_checker(cache) == 1)
    //         return (cache);
    //     if (line_checker(cache) == 2)
    //         result = ft_strjoin(result, cache);
    //     if (line_checker(cache) == 3)
    //     {
    //         middle_break = ft_split(cache);
    //         if (middle_break == NULL)
    //             return (NULL);
    //         cache = middle_break[1];
    //         return (middle_break[0]);
    //     }
    // }
    read_status = read(fd, buffer, BUFFER_SIZE);
    if (read_status == 0 || read_status == -1)
        return (NULL);
    buffer[read_status] = '\0';

    // while (line_checker(buffer) == 2)
    // {
    //     result = ft_strjoin(result, buffer);
    //     if (result == NULL)
    //         return (NULL);
    //     read_status = read(fd, buffer, BUFFER_SIZE);
    //     buffer[read_status] = '\0';
    // }
    // if (line_checker(buffer) == 1)
    // {
    //     result = ft_strjoin(result, buffer);
    //     if (result == NULL)
    //         return (NULL);
    // }
    // if (line_checker(buffer) == 3)
    // {
    //     middle_break = ft_split(buffer);
    //     if (middle_break == NULL)
    //         return (NULL);
    //     result = ft_strjoin(result, middle_break[0]);
    //     if (result == NULL)
    //         return (NULL);
    //     cache = middle_break[1];
    //     free(middle_break);
    // }
    return (result);
}

// int main(void)
// {
//     // char    *s;
//     // if (*s == '\0')
//     //     printf("sim\n");
//     int fd = open("../teste_gnl.txt", O_RDONLY);
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     // printf("%s", get_next_line(fd));
//     // printf("%s", get_next_line(fd));
//     return (0);
// }