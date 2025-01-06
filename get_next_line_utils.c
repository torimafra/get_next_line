/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:50:35 by vimafra-          #+#    #+#             */
/*   Updated: 2025/01/06 20:01:42 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// essa função conta quantos elementos de uma string até um caracter C
// pode ser usada para conseguir a length da string, se C = '\0', ou retornar o índice de qualquer outro caracter
int	strcounter(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

// CALLOC(), pois usar apenas a malloc() estava dando erros de variável não inicializada
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*temp;
	void			*ptr;
	size_t			i;

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

// duplicação com CALLOC()
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
	return (result);
}

// duplicação simples
// aqui temos a flag TYPE
// se TYPE == 0, a função copia SRC até o caracter C
// se TYPE == 1, a função copia SRC a partir do caracter C
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

// junta o conteúdo de duas strings, nesse programa basicamente usada para atualizar o conteúdo de RESULT
// RESULT vai ser passado em A, ele é passado como ponteiro para ponteiro para podermos alterar ele diretamente
char	*ft_strjoin(char **a, char *b)
{
	char	*result;
	int		len_a;
	int		len_b;

	if (!*a && !b)
		return (NULL);
	// como RESULT é inicializado como NULL, ele pode ser passado com esse valor
	if (!*a && b)
	{
		// então result vai ser apenas uma cópia de B
		result = ft_strdup(b);
		if (!result)
			return (NULL);
		return (result);
	}
	// função vai cair aqui se A (RESULT) já tiver alguma coisa
	len_a = strcounter(*a, '\0');
	len_b = strcounter(b, '\0');
	result = ft_calloc((len_a + len_b + 1), sizeof(char));
	if (result == NULL)
		return (NULL);
	// copia A para RESULT, até o fim dela
	strchrcopy(*a, result, '\0', 0);
	// copia B para RESULT, contando RESULT a partir da length de A
	strchrcopy(b, (result + strcounter(*a, '\0')), '\0', 0);
	// adiciona o terminator
	result[strcounter(*a, '\0') + strcounter(b, '\0')] = '\0';
	// dá free() em A, porque é o RESULT antigo
	// como ele foi alterado e vai ser substituido pelo novo RESULT, e vai ser perdido, ele precisa ser liberado aqui
	free(*a);
	return (*a = NULL, result);
}
