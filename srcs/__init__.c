#include "miniRT.h"

void    ft_zeroes(t_all *all)
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

static int  __parse_file(t_all *all)
{
    char    *str;
    char    *tmp;
    const int fd = open(all->argv[1], O_RDONLY);

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

int    __init__(t_all *all, char **argv)
{
    ft_zeroes(all);
    all->argv = argv;
    if (__parse_file(all))
        return(1);
    return (0);
}