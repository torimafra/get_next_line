/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:59:28 by vimafra-          #+#    #+#             */
/*   Updated: 2025/01/04 17:26:38 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_split(char **str, char **result, char **cache)
{
	char	*temp_result;
	char	*temp_cache;
	int		i;

	i = 0;
	while (str[0][i] != '\n' && str[0][i] != '\0')
		i++;
	temp_result = (char *)ft_calloc((i + 2), sizeof(char));
	temp_cache = ft_calloc((strcounter(*str, '\0') + 1), sizeof(char));
	if (!temp_result || !temp_cache)
		return (0);
	strchrcopy(*str, temp_result, '\n', 0);
	strchrcopy(*str, temp_cache, '\n', 1);
	free(*str);
	*str = NULL;
	*result = ft_strjoin(result, temp_result);
	if (!*result)
		return (free(temp_result), 0);
	if (*cache)
		free(*cache);
	*cache = ft_strdup(temp_cache);
	if (!*cache)
		return (free(temp_cache), 0);
	return (free(temp_cache), free(temp_result), 1);
}

char	*create_buffer(int fd)
{
	char	*buffer;
	int		read_status;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (buffer == NULL)
		return (NULL);
	read_status = read(fd, buffer, BUFFER_SIZE);
	if (read_status <= 0)
	{
		free(buffer);
		if (read_status < 0)
			return (NULL);
		if (read_status == 0)
			return ("");
	}
	return (buffer);
}

int	line_checker(char **str, char **result, char **cache)
{
	int	line_break;
	int	status;

	if (!*str)
		return (0);
	line_break = strcounter(*str, '\0') - strcounter(*str, '\n');
	if (line_break == 1 || line_break == 0)
	{
		*result = ft_strjoin(result, *str);
		if (!*result)
			return (-1);
		return (free(*cache), *cache = NULL, line_break);
	}
	if (line_break > 1)
	{
		status = ft_split(str, result, cache);
		if (status == 0)
			return (-1);
		return (line_break);
	}
	return (-1);
}

char	*buffer_handler(int fd, char **result, char **cache)
{
	char	*buffer;
	int		status;
	int		read_status;

	buffer = create_buffer(fd);
	if (!buffer)
		return (NULL);
	if (buffer[0] == '\0')
		return (*result);
	status = line_checker(&buffer, result, cache);
	if (status == -1)
		return (NULL);
	while (status == 0)
	{
		read_status = read(fd, buffer, BUFFER_SIZE);
		if (read_status < 0)
			return (free(buffer), buffer = NULL, NULL);
		if (read_status == 0)
			break ;
		buffer[read_status] = '\0';
		status = line_checker(&buffer, result, cache);
	}
	if (buffer)
		free(buffer);
	return (*result);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*cache = {NULL};
	int			status;

	result = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (cache)
	{
		status = line_checker(&cache, &result, &cache);
		if (status == -1)
			return (NULL);
		if (status == 1 || status > 1)
			return (result);
	}
	result = buffer_handler(fd, &result, &cache);
	return (result);
}
