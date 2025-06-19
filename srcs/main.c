#include "miniRT.h"
#include "tri_lib.h"

char	*readfile(int fd)
{
	int		rd;
	char	buf[BUFF_SIZE + 1];
	char	*final;

	final = NULL;
	while (1)
	{
		rd = read(fd, buf, BUFF_SIZE);
		if (!rd)
			break ;
		else if (rd == -1 && final)
			return (free(final), NULL);
		else if (rd == -1 && !final)
			return (NULL);
		buf[rd] = 0;
		final = ft_strjoin(final, buf);
	}
	return (final);
}

int	looped(t_tri_lib *t, void *a)
{
	(void)t;
	(void)a;
	while (1);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc < 2)
		return (printf("Not enough arguments\n"), 1);
	tri_lib()->init();
	tri_lib()->create_window("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 800, 600);
	all = __get_all();
	if (__init__(all, argv))
	{
		free_all(all);
		return (1);
	}
	free_all(all);
	tri_lib()->loop(looped, NULL);
	return (0);
}
