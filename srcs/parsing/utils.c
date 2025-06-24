#include "miniRT.h"

unsigned int	ft_atoi(char **s)
{
	unsigned int	n;

	n = 0;
	while (**s >= '0' && **s <= '9')
		n = n * 10 + *((*s)++) - '0';
	return (n);
}

double	ft_atof(char **s)
{
	int	n;
	int	dec;
	int	neg;

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
	dec = ft_atoi(s);
	return ((n + ((double)dec / pow(10, ft_nblen(dec)))) * neg);
}

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

int	skip_whitespace_hashtag(char **s, unsigned int *line_count)
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
	return (backslash_n);
}

int	skip_whitespace_hashtag_u(char **s, unsigned long *line_count)
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
	return (backslash_n);
}
