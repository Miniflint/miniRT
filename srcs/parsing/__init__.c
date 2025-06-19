#include "miniRT.h"

void	ft_zeroes(t_all *all)
{
	all->ambient_light.ratio = 0;
	all->ambient_light.rgb.r = 0;
	all->ambient_light.rgb.g = 0;
	all->ambient_light.rgb.b = 0;
	all->ambient_light.nb = 0;
	all->camera.viewpoint.x = 0;
	all->camera.viewpoint.y = 0;
	all->camera.viewpoint.z = 0;
	all->camera.nb = 0;
	all->camera.vec.x = 0;
	all->camera.vec.y = 0;
	all->camera.vec.z = 0;
	all->camera.fov = 0;
	all->line_count = 1;
	all->cylinders = 0;
	all->spheres = 0;
	all->planes = 0;
	all->lights = 0;
	all->argv = 0;
}

static int	__parse_file(t_all *all)
{
	char		*str;
	char		*tmp;
	const int	fd = open(all->argv[1], O_RDONLY);

	if (fd == -1)
		return (printf("File cannot be accessed\n"), 1);
	str = readfile(fd);
	if (!str)
		return (printf("File is empty/error occured while trying to read\n"), 1);
	tmp = str;
	if (__set_values(all, &str) == 1)
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

static int	check_ext(char **argv)
{
	int			i;
	const char	exts[2][4] = {".rt", ".obj"};
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

int	__init__(t_all *all, char **argv)
{
	ft_zeroes(all);
	all->argv = argv;
	if (check_ext(all->argv))
		return (1);
	if (__parse_file(all))
		return (1);
	if (all->ambient_light.nb <= 0)
		return (printf("Error: you must have 1 ambient light\n") > 1);
	if (all->camera.nb <= 0)
		return (printf("Error: you must have 1 camera\n") > 1);
	print_all_structs(all);
	return (0);
}
