#include "miniRT.h"

unsigned int	ft_atoi(char **s)
{
	unsigned int	n;

	n = 0;
	while (**s >= '0' && **s <= '9')
		n = n * 10 + *((*s)++) - '0';
	return (n);
}

double	ft_atofi(char **s)
{
	unsigned long long	n;
	short int			i;

	n = 0;
	i = 0;
	while ((*s)[i] >= '0' && (*s)[i] <= '9' && i <= 0b00001100)
		n = n * 10 + (*s)[i++] - '0';
	while ((*s)[i] >= '0' && (*s)[i] <= '9')
		++i;
	(*s) += i;
	return ((double)n / pow(10, i));
}

double	ft_atof(char **s)
{
	long long		n;
	double			dec;
	int				neg;

	neg = 1;
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			neg = -1;
		(*s)++;
	}
	n = ft_atoi(s);
	if (!(**s) || **s != '.')
		return ((double)n * neg);
	(*s)++;
	dec = ft_atofi(s);
	return ((n + dec) * neg);
}

int	skip_till_number(char **s, int nb)
{
	while (nb--)
		(*s)++;
	while (**s && !(**s >= '0' && **s <= '9')
		&& **s != '\n' && **s != '+' && **s != '-')
	{
		if (**s >= 33)
			return (3);
		(*s)++;
	}
	return (0);
}

int	skip_whitespace_hashtag(char **s, unsigned long *line_count)
{
	int	backslash_n;

	backslash_n = 3;
	while (ft_iswhitespace(**s) || **s == '#')
	{
		if (**s == '\n')
		{
			*line_count += 1;
			backslash_n = 0;
		}
		if (**s == '#')
			while (**s && **s != '\n')
				(*s)++;
		else
			(*s)++;
	}
	if (!**s)
		return (2);
	return (backslash_n);
}
