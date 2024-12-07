/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:50:35 by vimafra-          #+#    #+#             */
/*   Updated: 2024/12/07 18:00:40 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int line_checker(char *s)
{
    int i;

    i = 0;
    if (!s)
        return (0);
    while (s[i] != '\0')
    {
        if (s[i] == '\n')
            break ;
        i++;
    }
    if (i == (ft_strlen(s) - 1))
        return (1);
    if (i == ft_strlen(s))
        return (2);
    if (i < (ft_strlen(s) - 1))
        return (3);
    return (0);
}

char *ft_strjoin(char *a, char *b)
{
    int i = {0};
    int j = {0};
    char    *result;

    if(!b)
        b = "";
    if (!a)
    {
        result = (char *)malloc((ft_strlen(b) + 1) * sizeof(char));
    }
    else
        result = (char *)malloc((ft_strlen(a) + ft_strlen(b) + 1) * sizeof(char));
    if (result == NULL)
        return (NULL);
    if (a)
    {
        while (a[i] != '\0')
        {
            result[i] = a[i];
            i++;
        }
        free(a);
    }
    while (b[j] != '\0')
    {
        result[i] = b[j];
        i++;
        j++;
    }
    result[i] = '\0';
    return (result);
}

void ft_strcpy(char *src, char *dest, int type)
{
        int i = {0};
        int j = {0};

        if (type == 0)
        {
            while (src[i] != '\n')
            {
                dest[i] = src[i];
                i++;
            }
            dest[i] = '\n';
            dest[i + 1] = '\0';
        }
        if (type == 1)
        {
            while (src[i] != '\n')
                i++;
            while (src[i + 1] != '\0')
            {
                dest[j] = src[i + 1];
                i++;
                j++;
            }
            dest[j] = '\0';
        }
}

char **ft_split(char *str)
{
    int i;
    int j;
    char    **result;

    i = 0;
    j = 0;
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
    ft_strcpy(str, result[0], 0);
    ft_strcpy(str, result[1], 1);
    free(str);
    return (result);
}

// int main(void)
// {
//     char    *s;

//     if (!s)
//         printf("vazio\n");
//     //printf("%d\n", ft_strlen(s));
//     return (0);
// }