#include "miniRT.h"

void	iter_sphere(t_shape *shapes, t_all *all, int *i)
{
	t_sphere	*tmp;

	tmp = all->spheres;
	while (tmp)
	{
		shapes[*i].type = SPHERE;
		shapes[*i].shape = (void *)tmp;
		tmp = tmp->next;
		*i += 1;
	}
}

void	iter_cylinder(t_shape *shapes, t_all *all, int *i)
{
	t_cylinder	*tmp;

	tmp = all->cylinders;
	while (tmp)
	{
		shapes[*i].type = CYLINDER;
		shapes[*i].shape = (void *)tmp;
		tmp = tmp->next;
		*i += 1;
	}
}

void	iter_box(t_shape *shapes, t_all *all, int *i)
{
	t_box	*tmp;

	tmp = all->boxes;
	while (tmp)
	{
		shapes[*i].type = BOX;
		shapes[*i].shape = (void *)tmp;
		tmp = tmp->next;
		*i += 1;
	}
}

void	iter_obj(t_shape *shapes, t_all *all, int *i)
{
	t_object	*tmp;

	tmp = all->objects;
	while (tmp)
	{
		shapes[*i].type = OBJECT;
		shapes[*i].shape = (void *)tmp;
		tmp = tmp->next;
		*i += 1;
	}
}

t_shape	*create_shape_array(t_all *all)
{
	printf("%d\n", all->nb_shapes);
	int		i;
	t_shape	*shapes;

	shapes = malloc(sizeof(t_shape) * (all->nb_shapes + 1));
	if (!shapes)
		return (NULL);
	i = 0;
	iter_sphere(shapes, all, &i);
	iter_cylinder(shapes, all, &i);
	iter_box(shapes, all, &i);
	iter_obj(shapes, all, &i);
	if (i != all->nb_shapes)
		return (printf("WE GOT A PROBLEM\n"), free(shapes), NULL);
	shapes[i].type = END_SHAPE;
	shapes[i].shape = NULL;
	all->shapes = shapes;
	return (shapes);
}
