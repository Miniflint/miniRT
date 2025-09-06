/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __init__.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:05:24 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:06:23 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_zeroes(t_all *all)
{
	all->ambient_light.ratio = 0;
	all->ambient_light.rgb = (t_rgb){0, 0, 0, 0};
	all->ambient_light.nb = 0;
	all->camera.viewpoint = (t_coord){0, 0, 0};
	all->camera.nb = 0;
	all->camera.dir = (t_vec){0, 0, 0};
	all->camera.fov = 0;
	all->line_count = 1;
	all->cylinders = NULL;
	all->objects = NULL;
	all->spheres = NULL;
	all->planes = NULL;
	all->lights = NULL;
	all->win_width = WIN_WIDTH_ALL;
	all->win_height = WIN_HEIGHT_ALL;
	all->shadow_on = 1;
	all->canvas.pixel_values = 3;
	all->light_ratio = 1;
	all->distance_light = DISTANCE_LIGHT_MIDDLE * DISTANCE_LIGHT_MIDDLE;
}

int	__parse_file_scene(t_all *all)
{
	char		*str;
	char		*tmp;
	const int	fd = open(all->argv[1], O_RDONLY);

	if (fd == -1)
		return (printf("File cannot be accessed\n"), 1);
	str = readfile(fd);
	close(fd);
	if (!str)
		return (
			printf("File is empty/error occured while trying to read\n"), 1);
	tmp = str;
	if (__set_values_scene(all, &str) == 1)
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

void	zeroes_two(t_object *object, char *path)
{
	int	i;

	object->indexes[I_POINTS] = 0;
	object->indexes[I_FACES] = 0;
	object->i_vertice[I_VT] = 0;
	object->i_vertice[I_VN] = 0;
	object->i_vertice[I_V] = 0;
	object->nb_vertices = 0;
	object->line_count = 1;
	object->nb_points = 0;
	object->nb_faces = 0;
	object->name[0] = 0;
	object->coord = (t_coord){0, 0, 0};
	i = -1;
	while (path[++i])
		object->path[i] = path[i];
	object->path[i] = 0;
	while (++i < 256)
		object->path[i] = 0;
	i = -1;
	while (++i < 128)
		object->curr_group[i] = 0;
}

int	__init__(t_all *all, char **argv, int argc)
{
	ft_zeroes(all);
	all->argv = argv;
	all->argc = argc;
	if (check_ext(all->argv))
		return (1);
	if (__parse_file_scene(all))
		return (1);
	if (all->ambient_light.nb <= 0)
		return (printf("Error: you must have 1 ambient light\n"), 1);
	if (all->camera.nb <= 0)
		return (printf("Error: you must have 1 camera\n"), 1);
	apply_rgb_all_shape(all);
	if (__parse_file_objs(all))
		return (1);
	print_all_structs(all);
	make_perpendicular(&all->camera);
	cal_fov(all);
	return (0);
}
