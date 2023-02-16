/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:01:42 by lnicoter          #+#    #+#             */
/*   Updated: 2023/02/16 18:49:30 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	riferimenti:
		https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/

	linee guida per creare e fare get_next_line
	di base la funzione deve leggere una linea alla volta
	presente nel file decriptor
	ovvio che il return della funzione principale è la linea letta
	quindi una stringa
	tre funzioni disponibili da utilizzare:
		read(), malloc(), free()
	nozioni importanti di cui tenere conto:
		1) la funzione read()
		2) le variabili statiche
		3) la funzione open() che serve per testare il proprio lavoro nel main
	read():
		ritorna un valore size_t
		prototipo	size_t	read(int filedes, void *buf, size_t nbyte);
			prende un file descriptor (l'intero), un void chamato buf che è effettivamente un buffer
			e un altro size_t che è il numero di bytes
		quindi read prova a leggere n bytes che noi gli inviamo
		poi l'oggetto definito dal file descriptor al buffer puntato da buf
		quindi read() andrà a leggere da un file conservando ciò che ha letto in una variabile
		per esempio se volessi leggere cinque bytes all'interno del mio fd sarebbe tipo così credo:
		read(fd, pointer, 5); l'idea è questa e il return è il numero di bytes che è riuscito a leggere
		però se ha finito di leggere il file restituirà 0
		se ci sono problemi nella lettura restituirà invece -1
		sappi che quando leggi in un file la read si ricorda dov'è arrivato col buffer
		quindi se gli chiedo di leggere di nuovo partrà dalla lettera che non ha letto
		per esempio (ciao com'è?) read(fd, buf, 5) leggerà (ciao_) e se lo richiamo partirò dalla lettera c della parola com'è

	analizziamo però il problema della funzione in principio:
		allora il prototipo della funzione è: char	*get_next_line(int fd);
		sappiamo che il buffer viene definito alla compilazione quindi può cambiare
		se il buffer non è abbastanza grande dobbiamo tenere conto di quanto abbiamo letto
		nel buf e dobbiamo conservare la stringa letta in una varibile che possiamo chimare stash
		nella quale (secondo le regole di get_next_line) controlleremo se ha finito di essere letto
		visto che noi vogliamo leggere una linea
		poi appena troviamo il carattere che determina la fine della riga (\n) controlleremo se lo stash
		c'è l'ha e nel caso avesse copiato caratteri dopo questo dovremo inserire in una variabile chiamata
		line quello che abbiamo letto fino al carattere cha va a capo incluso quest'ultimo
		in seguito visto che abbiamo letto fino alla fine della linea possiamo dire allo stash di cancellare
		ciò che aveva prima del carattere a capo e tenere quelle in eccesso che non sono state messe nella line
		il subject dice che se chiamo get_next_line più volte o finché non finisce di leggere tutto il file
		ritornerà una linea alla volta. Ovvio che richiamandolo ancora noi avremo grazie alla read
		il puntatore puntato verso l'ultimo carattere letto, e grazie al fatto che stash è in realtà
		UNA VARIABILE STATICA manterremo i progressi della precedente lettura che in questo caso sarebbe
		le prime lettere dop<o il carattere separatore in seguito la lettura si ripete

	la domanda che mi pongo io però è come posso mettere il valore del buffer in stash?
	come diavolo posso cancellare lo stash senza eliminare i valori che si trovano prima del carattere a capo
	senza eliminare quelli che vengono dopo?
	come posso accingere ai valori del buffer e metterli nello stash?
*/

#include "get_next_line.h"

char	*ft_readrest(int fd, char *res)
{
	char	*temp;
	int		bytes;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(res, '\n') && bytes != 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free (temp);
			return (NULL);
		}
		temp[bytes] = '\0';
		res = ft_strjoin(res, temp);
	}
	free(temp);
	return (res);
}

char	*ft_writing(char *res)
{
	char	*line;
	int		i;

	i = 0;
	if (!res[i])
		return (NULL);
	while (res[i] && res[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (res[i] && res[i] != '\n')
	{
		line[i] = res[i];
		i++;
	}
	if (res[i] == '\n')
	{
		line[i] = res[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_new_static(char *res)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (!res[i])
	{
		free(res);
		return (NULL);
	}
	s = malloc(sizeof(char) * (ft_strlen(res) - i + 1));
	if (!s)
		return (NULL);
	i++;
	j = 0;
	while (res[i])
	{
		s[j++] = res[i++];
	}
	s[j] = '\0';
	free(res);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = ft_readrest(fd, rest);
	if (!rest)
		return (NULL);
	line = ft_writing(rest);
	rest = ft_new_static(rest);
	return (line);
}
