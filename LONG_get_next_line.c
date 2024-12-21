/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LONG_get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:59:28 by vimafra-          #+#    #+#             */
/*   Updated: 2024/12/18 11:01:54 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// int	line_checker(char *s)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == '\n')
// 			break ;
// 		i++;
// 	}
// 	if (i == (ft_strlen(s) - 1))
// 		return (1);
// 	if (i == ft_strlen(s))
// 		return (2);
// 	if (i < (ft_strlen(s) - 1))
// 		return (3);
// 	return (0);
// }

char	**ft_split(char *str)
{
	int		i;
	char	**result;

	i = 0;
	result = (char **)malloc(2 * sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (str[i] != '\n')
		i++;
	result[0] = (char *)malloc((i + 2) * sizeof(char));
	if (result[0] == NULL)
		return (NULL);
	result[1] = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (result[1] == NULL)
		return (NULL);
	copy_till_chr(str, result[0], '\n');
	result[0][ft_strlen(result[0])] = '\0';
	copy_from_chr(str, result[1], '\n');
	free(str);
	return (result);
}

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

    if (fd < 0 || BUFFER_SIZE <= 0)
    {
        ////printf("RETORNO 1\n");
        return (NULL);
    }
    if (cache)
    {
        ////printf("cache = %s", cache);
        if (cache && line_checker(cache) == 1)
        {
            //printf("JOIN01\n");
            result = ft_strjoin(result, cache);
            if (result == NULL)
            {
                ////printf("RETORNO 2\n");
                return (free(cache), NULL);
            }
            free(cache);
            cache = NULL;
            ////printf("RETORNO 2B\n");
            return (result);
        }
        if (cache && line_checker(cache) == 3)
        {
            middle_break = ft_split(cache);
            if (middle_break == NULL)
            {
                ////printf("RETORNO 3\n");
                return (free(cache), NULL);
            }
            cache = ft_strdup(middle_break[1]);
            free(middle_break[1]);
            //printf("JOIN02\n");
            result = ft_strjoin(result, middle_break[0]);
            free(middle_break[0]);
            free(middle_break);
            if (result == NULL)
            {
                ////printf("RETORNO 4\n");
                return (free(cache), NULL);
            }
            ////printf("RETORNO 4B\n");
            return (result);
        }
        if (cache && line_checker(cache) == 2)
        {
            //printf("JOIN03\n");
            result = ft_strjoin(result, cache);
            free(cache);
            if (result == NULL)
            {
                ////printf("RETORNO 4.5\n");
                return (NULL);
            }
            cache = NULL;
        }
    }
    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (buffer == NULL)
    {
        ////printf("RETORNO 5\n");
        return (NULL);
    }
    read_status = read(fd, buffer, BUFFER_SIZE);
    if (read_status < 0)
    {
        ////printf("RETORNO 6\n");
        return (free(buffer), NULL);
    }
    if (read_status == 0)
    {
        // printf("RETORNO 6.5\n");
        // printf("cache = %s", cache);
        if (result)
        {
            ////printf("1\n");
            return (free(buffer), result);
        }
        else
        {
            ////printf("2\n");
            return (free(buffer), free(result), NULL);
        }
    }
    buffer[read_status] = '\0';
    while (line_checker(buffer) == 2)
    {
        //printf("JOIN04\n");
        result = ft_strjoin(result, buffer);
        if (result == NULL)
        {
            ////printf("RETORNO 7\n");
            return (free(buffer), NULL);
        }
        read_status = read(fd, buffer, BUFFER_SIZE);
        if (read_status <= 0)
        {
            ////printf("RETORNO 8\n");
            break ;
        }
        buffer[read_status] = '\0';
    }
    if (line_checker(buffer) == 1)
    {
        //printf("JOIN05\n");
        result = ft_strjoin(result, buffer);
        if (result == NULL)
        {
            ////printf("RETORNO 9\n");
            return (free(buffer), NULL);
        }
        ////printf("RETORNO 9B\n");
        return (free(buffer), result);     
    }
    if (line_checker(buffer) == 3)
    {
        middle_break = ft_split(buffer); 
        if (middle_break == NULL)
        {
            ////printf("RETORNO 10\n");
            return (free(buffer), NULL);
        }
        // //printf("middle_break[0] = %s", middle_break[0]);
        // //printf("middle_break[1] = %s", middle_break[1]);
        // //printf("JOIN06\n");
        result = ft_strjoin(result, middle_break[0]);
        if (result == NULL)
        {
            free(middle_break[0]);
            free(middle_break[1]);
            free(middle_break);
            return (NULL);
        }
        free(middle_break[0]);
        if (middle_break[1][0] != '\0')
        {
            cache = ft_strdup(middle_break[1]);
            if(cache == NULL)
            {
                free(middle_break[1]);
                free(middle_break);
                free(result);
                return (NULL);
            }
        }
        free(middle_break[1]);
        free(middle_break);
        ////printf("RETORNO 12\n");
        ////printf("FINAL RETURN\n");
        //printf("CACHE = %s\n", cache);
        return (result);
    }
    else
        free(buffer);
    ////printf("RETORNO 13\n");
    return (result);
}

// int main(void)
// {
//     int fd = open("/nfs/homes/vimafra-/42/CommonCore/Projetos/read_error.txt", O_RDONLY);
//     char *line01 = get_next_line(fd);
//     char *line02 = get_next_line(fd);
//     char *line03 = get_next_line(fd);
//     char *line04 = get_next_line(fd);
//     char *line05 = get_next_line(fd);
    
//     printf("RETORNO = %s", line01);
//     printf("RETORNO = %s", line02);
//     printf("RETORNO = %s", line03);
//     printf("RETORNO = %s", line04);
//     printf("RETORNO = %s", line05);
//     free(line01);
//     free(line02);
//     free(line03);
//     free(line04);
//     //free(line05);
//     // //printf("RETORNO = %s", get_next_line(fd));
//     // //printf("RETORNO = %s", get_next_line(fd));
//     // //printf("RETORNO = %s", get_next_line(fd));
//     // //printf("RETORNO = %s", get_next_line(fd));

//     return (0);
// }