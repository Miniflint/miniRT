#include "miniRT.h"

void	free_pts(t_point *point)
{
	if (!point)
		return ;
	free_pts(point->next);
	free(point);
}

t_object	*free_objs(t_object *obj)
{
	unsigned long	i;

	if (!obj)
		return (NULL);
	free_objs(obj->next);
	if (obj->nb_vertices)
		free(obj->vertices);
	if (obj->nb_vt)
		free(obj->vt);
	if (obj->nb_vn)
		free(obj->vn);
	if (obj->faces)
		free(obj->faces);
	i = -1;
	while (obj->nb_points && i < obj->nb_points)
		free_pts(++i + obj->points);
	free(obj);
	return (NULL);
}
