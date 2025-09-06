/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:06:05 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:06:11 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_nblen(int nb)
{
	int	i;

	i = 0;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp_ptr;

	tmp_ptr = (unsigned char *)b;
	while (len > 0)
	{
		*(tmp_ptr++) = (unsigned char)c;
		len--;
	}
	return (b);
}

int	ft_iswhitespace(char c)
{
	if (c == ' ' || (c >= 8 && c <= 13))
		return (1);
	return (0);
}

int	ft_strncmp(char *s1, const char *s2, size_t n)
{
	size_t	x;

	x = 0;
	if (n == 0)
		return (0);
	while (s1[x] && s2[x] && s1[x] == s2[x] && x < n - 1)
		x++;
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}
