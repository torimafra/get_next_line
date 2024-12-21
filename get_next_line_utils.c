/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:50:35 by vimafra-          #+#    #+#             */
/*   Updated: 2024/12/21 15:14:26 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	strcounter(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	unsigned char *temp;
	size_t	i;

	i = 0;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > (size_t)(-1) / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	temp = (unsigned char *)(ptr);
	while (i < nmemb * size)
	{
		temp[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*ft_strdup(char *s)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_calloc((strcounter(s, '\0') + 1), sizeof(char));
	while (s[i] != '\0')
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	//printf("S PTR = %p\n", s);
	return (result);
}

void	strchrcopy(char *src, char *dest, char c, int type)
{
	int	i;

	i = 0;
	if (type == 0)
	{
		while (src[i] != c && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		if (c == '\n')
			dest[i] = '\n';
	}
	if (type == 1)
	{
		while (src[i] != c && src[i] != '\0')
			i++;
		while (src[i + 1] != '\0')
		{
			*dest = src[i + 1];
			i++;
			dest++;
		}
	}
}

char	*ft_strjoin(char *a, char *b)
{
	char	*result;

	if (!a && !b)
		return (NULL);
	if (!a && b)
	{
		result = ft_strdup(b);
		if (!result)
			return (NULL);
		return (result);
	}
	if (a && !b)
	{
		result = ft_strdup(a);
		if (!result)
			return (NULL);
		return (result);
	}
	result = ft_calloc((strcounter(a, '\0') + strcounter(b, '\0') + 1), sizeof(char));
	if (result == NULL)
		return (NULL);
	strchrcopy(a, result, '\0', 0);
	strchrcopy(b, (result + strcounter(a, '\0')), '\0', 0);
	result[strcounter(a, '\0') + strcounter(b, '\0')] = '\0';
	//printf("A PTR = %p\n", a);
	free(a);
	return (result);
}