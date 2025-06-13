#include "miniRT.h"

int ft_nblen(int nb)
{
    int i;

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
	int i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

void skip_till_number(char **s)
{
    while (**s && !(**s >= '0' && **s <= '9') && **s != '\n' && (**s != '+' && **s != '-'))
        (*s)++;
}

int skip_whitespace_hashtag(char **s)
{
    int backslash_n;

    backslash_n = 1;
    while (ft_iswhitespace(**s) || **s == '#')
    {
        if (**s == '\n')
            backslash_n = 0;
        if (**s == '#')
            while (**s && **s != '\n')
                (*s)++;
        else
            (*s)++;
    }
    return (backslash_n);
}