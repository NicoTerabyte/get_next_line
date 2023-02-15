/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prove_con_read_open.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:01:55 by lnicoter          #+#    #+#             */
/*   Updated: 2023/02/14 18:44:27 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(int argc, char *argv[])
{
	int		fd;
	char	*buf;
	char	*line;
	int		let;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	fd = open("prova.txt", O_RDONLY);
	let = read(fd, buf, BUFFER_SIZE);
	buf[let] = '\0';
	printf("Those bytes are as follows: %s\n", buf);
	close(fd);
	return (0);
}
