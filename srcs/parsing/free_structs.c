#include "miniRT.h"

t_light 	*free_l(t_light *light)
{
	if (!light)
		return (NULL);
	free_l(light->next);
	free(light);
	return (NULL);
}

t_sphere	*free_sp(t_sphere *sphere)
{
	if (!sphere)
		return (NULL);
	free_sp(sphere->next);
	free(sphere);
	return (NULL);
}

t_plane	*free_pl(t_plane *plane)
{
	if (!plane)
		return (NULL);
	free_pl(plane->next);
	free(plane);
	return (NULL);
}

t_cylinder	*free_cy(t_cylinder *cylinder)
{
	if (!cylinder)
		return (NULL);
	free_cy(cylinder->next);
	free(cylinder);
	return (NULL);
}

void	free_all(t_all *all)
{
	all->lights = free_l(all->lights);
	all->spheres = free_sp(all->spheres);
	all->planes = free_pl(all->planes);
	all->cylinders = free_cy(all->cylinders);
	all->objects = free_objs(all->objects);
}
