/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:59:28 by vimafra-          #+#    #+#             */
/*   Updated: 2024/12/21 15:14:32 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_split(char **str, char **result, char **cache)
{
	int		i;
    char *temp_result;
    char *temp_cache;

    i = 0;
	while (str[0][i] != '\n' && str[0][i] != '\0')
		i++;
	temp_result = (char *)ft_calloc((i + 2), sizeof(char));
	if (!temp_result)
		return (0);
	temp_cache = ft_calloc((strcounter(*str, '\0') + 1), sizeof(char));
	if (!temp_cache)
		return (0);
	strchrcopy(*str, temp_result, '\n', 0);
	strchrcopy(*str, temp_cache, '\n', 1);
    free(*str);
    *str = NULL;
    *result = ft_strjoin(*result, temp_result);
    if (!*result)
        return (free(temp_result), 0);
    *cache = ft_strdup(temp_cache);
    //printf("THE CULPRIT = %p\n", *cache);
    if (!*cache)
        return (free(temp_cache), 0);
    return (free(temp_cache), free(temp_result), 1);
}

char *create_buffer(int fd, char **result)
{
    char *buffer;
    int read_status;
    
    buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
    if (buffer == NULL)
        return (NULL);
    read_status = read(fd, buffer, BUFFER_SIZE);
    if (read_status < 0)
        return (free(buffer), NULL);
    if (read_status == 0)
    {
        if (result)
            return (free(buffer), *result);
        else
            return (free(buffer), NULL);
    }
    buffer[read_status] = '\0';
    return (buffer);
}

// int	line_checker(char **str, char **result, char **cache) //cache, result, cache
// {
// 	int	i;
// 	int status;

//     if (!*str)
// 		return (0);
// 	i = strcounter(*str, '\n');
//     //printf("I CHECKER = %d\n", i);
//     //printf("STRCOUNTER CHECKER = %d\n", (strcounter(*str, '\0')));
// 	if (i == (strcounter(*str, '\0') - 1) || i == strcounter(*str, '\0'))
// 	{
//         //printf("VERIFICAR PTR = %p\n", *str);
//         *result = ft_strjoin(*result, *str);
//         //printf("STR PTR = %p\n", *str);
//         //printf("STR = %s\n", *str);
//         if (!*result)
//         {
//             //printf("AAA\n");
//             return (free(*str), 0);
//         }
// 		if (i == (strcounter(*str, '\0') - 1))
//         {
// 			//printf("BBB\n");
//             return (*cache = NULL, 1);
//         }
// 		if (i == strcounter(*str, '\0'))
//         {
// 			//printf("CCC\n");
//             //printf("STR = %s\n", *str);
//             if (&*str == &*cache)
//                 free(*str);
//             return (*cache = NULL, 2);
//         }
// 	}
// 	if (i < (strcounter(*str, '\0') - 1))
// 	{
// 		 status = ft_split(str, result, cache);
//         if (status == 0)
//             return (0);
//         return (3);
// 	}
// 	return (0);
// }

int	line_checker(char **str, char **result, char **cache) //cache, result, cache
{
	int	i;
	int status;
    int check;

    if (!*str)
		return (0);
	i = strcounter(*str, '\n');

	if (i == (strcounter(*str, '\0') - 1) || i == strcounter(*str, '\0'))
	{
        if (i == (strcounter(*str, '\0') - 1))
            check = 1;
		if (i == strcounter(*str, '\0'))
            check = 2;
        *result = ft_strjoin(*result, *str);
        if (!*result)
            return (free(*str), 0);
        // if (&*str == &*cache)
        //     free(*str);
        return (*cache = NULL, check);	
	}
	if (i < (strcounter(*str, '\0') - 1))
	{
		 status = ft_split(str, result, cache);
        if (status == 0)
            return (0);
        return (3);
	}
	return (0);
}


char *buffer_handler(int fd, char **result, char **cache)
{
    char *buffer;
    int status;
    int read_status;

    buffer = create_buffer(fd, result);
     if (!buffer)
        return (NULL);
    if (buffer[0] == '\0')
        return (free(buffer), *result); 
    status = line_checker(&buffer, result, cache);
    if (status == 0)
        return (NULL);
    while (status == 2)
    {
        read_status = read(fd, buffer, BUFFER_SIZE);
        if (read_status < 0)
                return (free(buffer), NULL);
        buffer[read_status] = '\0';
        status = line_checker(&buffer, result, cache);
    }
    return (free(buffer), *result);
}

char *get_next_line(int fd)
{
    char    *result;
    static char    *cache = {NULL};
    int status;

    result = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (cache)
    {
        status = line_checker(&cache, &result, &cache);
        if (status == 0)
            return (NULL);
        if (status == 1 || status == 3)
            return (result);
    }
    result = buffer_handler(fd, &result, &cache);
    return (result);
}

// int main(void)
// {
// 	int fd = open("../teste_gnl.txt", O_RDONLY);
//     printf("FD = %d\n", fd);
//     // char *line01 = get_next_line(fd);
//     // char *line02 = get_next_line(fd);
//     //char *line03 = get_next_line(fd);
//     // char *line04 = get_next_line(fd);

//     //printf("RETORNO = %s", line01);
//     //printf("RETORNO = %s", line02);
//     ////printf("RETORNO = %s", line03);
//     // //printf("RETORNO = %s", line04);
//     // free(line01);
//     // free(line02);
//     //free(line03);
// 	return (0);
// }
