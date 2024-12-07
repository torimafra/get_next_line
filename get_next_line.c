/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:59:28 by vimafra-          #+#    #+#             */
/*   Updated: 2024/12/07 18:06:28 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_strdup(char *s)
{
    char *result;
    int i;

    i = 0;
    result = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
    while (s[i] != '\0')
    {
        result[i] = s[i];
        i++;
    }
    result[i] = '\0';
    return (result);
}

char *get_next_line(int fd)
{
    char    *buffer = {NULL};
    char    *result = {NULL};
    static char    *cache = {NULL};
    char    **middle_break;
    int read_status;

    if (fd <= 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (cache)
    {
        if (line_checker(cache) == 1)
        {
            result = ft_strjoin(result, cache);
            free(cache);
            return (result);
        }
        if (line_checker(cache) == 2)
        {
            result = ft_strjoin(result, cache);
            free(cache);
        }
        if (line_checker(cache) == 3)
        {
            middle_break = ft_split(cache);
            if (middle_break == NULL)
                return (NULL);
            cache = ft_strdup(middle_break[1]);
            free(cache);
            return (middle_break[0]);
        }
    }
    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (buffer == NULL)
        return (NULL);
    read_status = read(fd, buffer, BUFFER_SIZE);
    if (read_status <= 0)
    {
        free(buffer);
        return (NULL);
    }
    buffer[read_status] = '\0';
    while (line_checker(buffer) == 2)
    {
        //printf("1\n");
        result = ft_strjoin(result, buffer);
        if (result == NULL)
            return (NULL);
        read_status = read(fd, buffer, BUFFER_SIZE);
        buffer[read_status] = '\0';
        //printf("buffer = %s\n", buffer);
    }
    if (line_checker(buffer) == 1)
    {
        //printf("2\n");
        result = ft_strjoin(result, buffer);
        if (result == NULL)
            return (free(buffer), NULL);
        
    }
    if (line_checker(buffer) == 3)
    {
        //printf("3\n");
        middle_break = ft_split(buffer); 
        if (middle_break == NULL)
            return (NULL);
        result = ft_strjoin(result, middle_break[0]);
        if (result == NULL)
            return (NULL);
        free(middle_break[0]);
        cache = ft_strdup(middle_break[1]);
        free(middle_break[1]);
        free(middle_break);
    }
    else
        free(buffer);
    return (result);
}

int main(void)
{
    // char    *s;
    // if (*s == '\0')
    //     //printf("sim\n");
    int fd = open("../teste_gnl.txt", O_RDONLY);
    char *line = get_next_line(fd);
    
    printf("RETORNO = %s", line);
    free(line);
    ////printf("%s", get_next_line(fd));
    // //printf("%s", get_next_line(fd));
    // //printf("%s", get_next_line(fd));
    return (0);
}