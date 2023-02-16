/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:20:59 by lnicoter          #+#    #+#             */
/*   Updated: 2023/02/16 18:42:51 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *back, char *buff)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!back)
	{
		back = malloc(1 * sizeof(char));
		back[0] = '\0';
	}
	if (!back || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(back) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (back)
		while (back[++i] != '\0')
			str[i] = back[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(back) + ft_strlen(buff)] = '\0';
	free (back);
	return (str);
}

char	*ft_strchr(char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
