/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:05:44 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:06:12 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int			i;
	char *const	tmp = s1;
	char		*new_str;

	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	if (s1)
		while (*s1)
			new_str[i++] = *(s1++);
	if (s1)
		free(tmp);
	if (s2)
		while (*s2)
			new_str[i++] = *(s2++);
	new_str[i] = 0;
	return (new_str);
}

static int	in_readfile(char **final, char **buf, int fd, int i)
{
	ssize_t	rd;

	rd = (BUFF_SIZE << i);
	(*buf) = malloc(sizeof(char) * (rd + 1));
	if (!(*buf))
		return (printf("Error: buffer malloc\n"), 0);
	rd = read(fd, (*buf), rd);
	if (!rd)
		return (2);
	else if (rd == -1 && (*final))
		return (free((*buf)), free((*final)), 0);
	else if (rd == -1 && !(*final))
		return (free((*buf)), 0);
	(*buf)[rd] = 0;
	(*final) = ft_strjoin((*final), (*buf));
	if (!(*final))
		return (free((*buf)), printf("Error: buffer malloc error\n"), 0);
	free((*buf));
	return (1);
}

char	*readfile(int fd)
{
	int		code;
	char	*buf;
	char	*final;
	int		i;

	final = NULL;
	i = 0;
	while (1)
	{
		code = in_readfile(&final, &buf, fd, i);
		if (!code)
			return (NULL);
		else if (code == 2)
			break ;
		i += (i < 18);
	}
	free(buf);
	return (final);
}
