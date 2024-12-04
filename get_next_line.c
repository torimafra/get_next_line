/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:55:39 by vimafra-          #+#    #+#             */
/*   Updated: 2024/12/04 13:58:32 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_eol(char *s)
{
	int	i;

    i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char    *substr(char *s, unsigned int end)
{
    char    *result;
    unsigned int	i;

    i = 0;
	result = (char *)malloc((end + 1) * sizeof(char));
    if (result == NULL)
        return (NULL);
    while (s[i] != '\0' && i <= end)
	{
		result[i] = s[i];
		i++;
	}
	return (result);
}

int line_checker(char *s)
{
    if (find_eol(s) == (ft_strlen(s) - 1)) // Se a quebra de linha for o último caracter do buffer
        return (1);
    if (find_eol(s) == -1) // Se não tiver \n
        return (2);
    if (find_eol(s) != -1) // Se tiver quebra de linha no buffer
        return (3);
    return (0);

}

char *get_next_line(int fd)
{
    char    *gnl_buffer;
    int read_status;
    static char    *temp;
    char *result;

    if (fd == -1 || BUFFER_SIZE == 0)
        return (NULL);
    result = NULL;
    if(temp[0] != '\0')
    {
        if (line_checker(temp) == 1)
        {
            result = ft_strjoin(result, temp);
            if (result == NULL)
                return (NULL);
            return (result);
        }
        if (line_checker(temp) == 2)
        {
            result = ft_strjoin(result, temp);
            if (result == NULL)
                return (NULL);   
        }
        if (line_checker(temp) == 3)
        {
            result = ft_strjoin(result, substr(temp, find_eol(temp)));
            if (result == NULL)
                return (NULL);
            temp = temp + (find_eol(temp) + 1);
            return (result);
        }
    }
    gnl_buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
    if (gnl_buffer == NULL)
        return (NULL);
    read_status = read(fd, gnl_buffer, BUFFER_SIZE);
     if (read_status == -1 || read_status == 0)
         return (NULL);
    while (line_checker(gnl_buffer) == 2) // Acho que precisa checar isso primeiro pq é o único que vai precisar ficar relendo e preenchendo a lista
    {
        result = ft_strjoin(result, gnl_buffer);
        if (result == NULL)
            return (NULL);
        set_null(gnl_buffer);
        read_status = read(fd, gnl_buffer, BUFFER_SIZE);
        if (read_status == -1 || read_status == 0)
            return (NULL);
    }
    if (line_checker(gnl_buffer) == 1)
    {
            result = ft_strjoin(result, gnl_buffer);
            if (result == NULL)
                return (NULL);
    }
    if (line_checker(gnl_buffer) == 3)
    {
        result = ft_strjoin(result, substr(gnl_buffer, find_eol(gnl_buffer)));
        if (result == NULL)
                return (NULL);
        temp = gnl_buffer + (find_eol(gnl_buffer) + 1);
        printf("temp = %s\n", temp);
    }
    
    return (result);
}

int main(void)
{
    int fd = open("../teste_gnl.txt", O_RDONLY);
    printf("RETORNO = %s", get_next_line(fd));
    printf("RETORNO = %s", get_next_line(fd));
    //printf("RETORNO = %s", get_next_line(fd));
    //get_next_line(fd);
    return (0);
}