/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:59:28 by vimafra-          #+#    #+#             */
/*   Updated: 2025/01/06 18:41:30 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// essa função SPLIT divide uma string no caracter \n
// ela recebe as três string strings por endereço, para poder alterá-las diretamente
int	ft_split(char **str, char **result, char **cache)
{
	char	*temp_result;
	char	*temp_cache;
	int		i;

	i = 0;
	// percorre STR procurando \n, e pega seu índice
	// a SPLIT só vai ser chamada se uma string tiver um \n, então assumimos que ele vai ser encontrado
	while (str[0][i] != '\n' && str[0][i] != '\0')
		i++;
	// temp_result vai guardar o trecho de STR até (e contendo) a quebra de linha, ou seja, o que vai ser adicionado a RESULT
	// adicionamos 2 para o caracter \n e o \0
	temp_result = (char *)ft_calloc((i + 2), sizeof(char));
	// temp_cache vai guardar temporariamente o que vai ser adicionado ao CACHE
	temp_cache = ft_calloc((strcounter(*str, '\0') + 1), sizeof(char));
	// proteções das alocações
	if (!temp_result || !temp_cache)
		return (0);
	// STRCHRCOPY faz uma cópia simples de uma string, aproveitando que os TEMP já foram alocados
	strchrcopy(*str, temp_result, '\n', 0);
	strchrcopy(*str, temp_cache, '\n', 1);
	// com os dois conteúdos dividos e copiados, STR pode ser liberada
	free(*str);
	// e setada como NULL novamente
	*str = NULL;
	// adicionamos o conteúdo de TEMP_RESULT a RESULT
	*result = ft_strjoin(result, temp_result);
	// proteção do malloc
	if (!*result)
		return (free(temp_result), 0);
	// se o cache já tiver alguma coisa, dar free
	if (*cache)
		free(*cache);
	// adicionar o novo conteúdo ao CACHE
	*cache = ft_strdup(temp_cache);
	// proteção do malloc
	if (!*cache)
		return (free(temp_cache), 0);
	// se tudo deu certo, dá free nos dois TEMP e retorna 1
	return (free(temp_cache), free(temp_result), 1);
}

// essa função cria o BUFFER que vai usado pela função READ()
// e o preenche com a primeira leitura
char	*create_buffer(int fd)
{
	char	*buffer;
	int		read_status;

	// alocação de memória para o BUFFER, usando o BUFFER_SIZE dado no .h ou passado na hora da compilação
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	//proteção da alocação
	if (buffer == NULL)
		return (NULL);
	// a função READ() retorna a quantidade de bytes lidos
	read_status = read(fd, buffer, BUFFER_SIZE);
	// se retornar zero ou negativo, significa que não tem mais nada para ler, ou que houve erro de leitura
	if (read_status <= 0)
	{
		//em ambos os casos, devemos liberar o BUFFER, pois ele não vai ser mais usado
		free(buffer);
		// se o READ_STATUS for negativo, retornar NULL, pois houve erro
		if (read_status < 0)
			return (NULL);
		// se for zero, retorno uma string vazia para diferenciar do status negativo
		// pois talvez ainda haja algo para retornar guardado no RESULT, a ser checado posteriormente
		if (read_status == 0)
			return ("");
	}
	// se a leitura der certo, retorno o que foi lido e está guardado no BUFFER
	return (buffer);
}

// essa função checa o conteúdo de uma string STR (no caso desse programa, do BUFFER ou do CACHE)
// e indica se ela contém um trecho de linha, uma linha inteira ou uma linha e mais
// ela recebe RESULT e CACHE como ponteiros para ponteiros, para poder alterá-los diretamente usando seus endereços
int	line_checker(char **str, char **result, char **cache)
{
	int	line_break;
	int	status;

	// se STR for nula, retorna zero 
	if (!*str)
		return (0);
	// aqui fazemos a diferença entre o fim da string (length) e o índice do caracter da quebra de linha
	line_break = strcounter(*str, '\0') - strcounter(*str, '\n');
	// se length - (quebra de linha) for um, significa que STR contém exatamente uma linha inteira, já que \n é o último caracter antes de \0
	// se length - (quebra de linha) for zero, signifca que STR tem apenas um trecho de linha, já que a contagem para o caracter \n também chegou até o final da string
	// ou seja, não achou \n até o final da string
	if (line_break == 1 || line_break == 0)
	{
		// em ambos os casos, RESULT é atualizado com a adição do conteúdo de STR
		*result = ft_strjoin(result, *str);
		// FT_STRJOIN usa calloc, então temos a proteção do retorno
		if (!*result)
			return (-1);
		// libera o cache, seta ele como NULL novamente, e retorna line break, ou seja, uma indicação do que foi encontrado em STR
		return (free(*cache), *cache = NULL, line_break);
	}
	// se length - (quebra de linha) for maior do que um, signifca que \n está antes do fim de STR, ou seja, STR contém uma linha inteira e mais um pouco
	if (line_break > 1)
	{
		// nesse caso, usando a função FT_SPLIT, atualizamos RESULT com a linha inteira encontrada, e CACHE com o que está após a quebra de linha
		status = ft_split(str, result, cache);
		//FT_SPLIT usa calloc, então temos a proteção do retorno
		if (status == 0)
			return (-1);
		//aqui não liberamos o CACHE, pois ele acabou de ser preenchido, e retorna line break, uma indicação do que foi encontrado em STR
		return (line_break);
	}
	// se ocorrer algum erro, retorna -1
	return (-1);
}

// essa função cria o BUFFER, chamando a CREATE_BUFFER()
// e lida com o resultado do BUFFER criado (se ele já pode ser retornado ou se é necessário fazer mais leituras)
char	*buffer_handler(int fd, char **result, char **cache)
{
	char	*buffer;
	int		status;
	int		read_status;

	// cria e guarda a primeira leitura do BUFFER
	buffer = create_buffer(fd);
	// se o BUFFER for nulo, houve erro, retornar nulo
	if (!buffer)
		return (NULL);
	// se o BUFFER for vazio, retornar RESULT
	// vai retornar nulo se o RESULT estiver vazio também, ou o valor guardado nele, se houver
	if (buffer[0] == '\0')
		return (*result);
	// checa o BUFFER recebido, se ele contém um trecho de linha, uma linha inteira, ou uma linha e mais
	// a cada chamada do LINE_CHECKER(), a string RESULT é atualizada com o conteúdo lido, e o CACHE também, se houver
	status = line_checker(&buffer, result, cache);
	// se o status for -1, houve erro, retornar nulo
	if (status == -1)
		return (NULL);
	// se o status for 0, significa que temos apenas um trecho de linha
	// e que mais leituras precisam ser feitas, até chegar ao final dela
	while (status == 0)
	{
		// nova leitura
		read_status = read(fd, buffer, BUFFER_SIZE);
		// se READ_STATUS for negativo, houve erro, retornar nulo
		if (read_status < 0)
			return (free(buffer), buffer = NULL, NULL);
		// se READ_STATUS for zero, não há mais nada para ler, sair desse loop
		if (read_status == 0)
			break ;
		//adiciona o terminator de string no final de BUFFER
		buffer[read_status] = '\0';
		// checa a linha lida para ver se chegamos ao fim da linha ou não
		status = line_checker(&buffer, result, cache);
	 	// se ainda não chegamos, o status vai ser zero novamente, e o loop continua lendo
		// se sim, sai do loop
	}
	// se houver algo ainda guardado no BUFFER, libera
	if (buffer)
		free(buffer);
	// retorna RESULT
	return (*result);
}

char	*get_next_line(int fd)
{
	char		*result;
	// variável estática é inicializada como NULL
	// precisa ser inicializada dessa maneira, porque se fosse inicializada abaixo como o RESULT, ela seria setada como NULL toda vez que a função rodasse de novo
	// perdendo o que está guardado dentro dela
	static char	*cache = {NULL};
	int			status;

	result = NULL;
	// checa erro de FD e BUFFER_SIZE inválido
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// executa se houver CACHE
	if (cache)
	{
		// checa a string que está dentro do CACHE
		status = line_checker(&cache, &result, &cache);
		// se der algum erro
		if (status == -1)
			return (NULL);
		// se o CACHE contiver uma linha inteira ou uma linha + um pedaço, já retorna o RESULT
		// porque no último caso, a LINE_CHECKER() já guarda o pedaço novamente no CACHE e deixa o RESULT pronto
		if (status == 1 || status > 1)
			return (result);
	}
	// função segue pra cá se o CACHE contiver apenas um pedaço de linha, e a leitura precisar continuar
	result = buffer_handler(fd, &result, &cache);
	return (result);
}
