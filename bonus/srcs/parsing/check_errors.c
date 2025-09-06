#include "miniRT.h"

int	__parse_file_objs(t_all *all)
{
	int		i;

	i = 2;
	while (i < all->argc)
	{
		all->objects = create_obj_path(&all->objects, all->argv[i]);
		if (!all->objects)
			return (1);
		i++;
	}
	return (0);
}

int	check_ext(char **argv)
{
	int			i;
	const char	exts[2][5] = {".rt", ".obj"};
	int			max_len_str;
	int			max_len_ext;

	i = 1;
	while (argv[i])
	{
		max_len_str = ft_strlen(argv[i]);
		max_len_ext = ft_strlen((char *)exts[i > 1]);
		if (max_len_ext > max_len_str)
			return (printf("Error: extension doesn't match: %s\n",
					exts[i > 1]), 1);
		while (max_len_ext > 0 && max_len_str > 0
			&& argv[i][max_len_str] == exts[i > 1][max_len_ext])
		{
			max_len_str--;
			max_len_ext--;
		}
		if (argv[i][max_len_str] != exts[i > 1][max_len_ext])
			return (printf("Extension doesn't match %s\n", exts[i > 1]), 1);
		i++;
	}
	return (0);
}
