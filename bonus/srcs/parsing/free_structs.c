#include "miniRT.h"

t_light	*free_l(t_light *light)
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

t_box	*free_bx(t_box *box)
{
	if (!box)
		return (NULL);
	free_bx(box->next);
	free(box);
	return (NULL);
}

unsigned long get_depth_objs(t_object *root)
{
	if (!root)
		return (0);
	return (get_depth_objs(root->next), root->nb_faces);
}

int	free_all(void *content)
{
	t_all	*all;
	unsigned long	nb_objs; 

	all = content;
	end_thread(all, all->n_thread);
	all->lights = free_l(all->lights);
	all->spheres = free_sp(all->spheres);
	all->planes = free_pl(all->planes);
	all->cylinders = free_cy(all->cylinders);
	all->boxes = free_bx(all->boxes);
	nb_objs = get_depth_objs(all->objects);
	all->objects = free_objs(all->objects);
	free(all->shapes);
	if (free_hitboxes(all->bvh, 2 * (all->nb_shapes + nb_objs)))
		return (printf("error freeing\n"), 1);
	return (0);
}
