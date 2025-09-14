#include "miniRT.h"

void	set_spherical_object(void *object, int type)
{
	t_sphere *const		sphere = (t_sphere *)object;
	t_cylinder *const	cyl = (t_cylinder *)object;

	if (type == SPHERE)
	{
		sphere->radius = sphere->diameter / 2;
		sphere->radius_squared = sphere->radius * sphere->radius;
	}
	else if (type == CYLINDER)
	{
		cyl->radius = cyl->diameter / 2;
		cyl->radius_squared = cyl->radius * cyl->radius;
	}
}

int	get_sphere(t_sphere **head, char **const restrict s)
{
	t_sphere *const	sphere = create_empty_node(sizeof(t_sphere) * 1);

	if (!sphere)
		return (1);
	if (skip_till_number(s, 2))
		return (free(sphere), 3);
	if (get_coord(&sphere->coord, s))
		return (free(sphere), printf("\tSpheres problem\n"), 1);
	if (skip_till_number(s, 0))
		return (free(sphere), 3);
	sphere->diameter = ft_atof(s);
	if (sphere->diameter < 0.00)
		return (free(sphere),
			printf("Error: Spheres radius value < 0.0\n"), 1);
	set_spherical_object(sphere, SPHERE);
	if (skip_till_number(s, 0))
		return (free(sphere), 3);
	if (get_rgb(&sphere->rgb_save, s))
		return (free(sphere), printf("\tSpheres problem\n"), 1);
	if (get_material(&sphere->material, s))
		return (3);
	sphere->color = argb_to_rgbf(sphere->rgb_save);
	sphere->next = *head;
	*head = sphere;
	if (!**s)
		return (2);
	return (skip_whitespace_hashtag(s, &(__get_all()->line_count)));
}

int	get_plane(t_plane **head, char **const restrict s)
{
	t_plane	*plane;

	plane = (t_plane *)create_empty_node(sizeof(t_plane) * 1);
	if (!plane)
		return (1);
	if (skip_till_number(s, 2))
		return (free(plane), 3);
	if (get_coord(&plane->coord, s))
		return (free(plane), printf("\tPlanes problems\n"), 1);
	if (skip_till_number(s, 0))
		return (free(plane), 3);
	if (get_vec(&plane->vec, s))
		return (free(plane), printf("\tPlanes problems\n"), 1);
	if (skip_till_number(s, 0))
		return (free(plane), 3);
	if (get_rgb(&plane->rgb_save, s))
		return (free(plane), printf("\tPlanes problems\n"), 1);
	if (get_material(&plane->material, s))
		return (1);
	plane->color = argb_to_rgbf(plane->rgb_save);
	plane->next = *head;
	*head = plane;
	if (!**s)
		return (2);
	return (skip_whitespace_hashtag(s, &(__get_all()->line_count)));
}

t_cylinder	*create_cylinder(char **const restrict s, int *code)
{
	t_cylinder *const	cylinder = create_empty_node(sizeof(t_cylinder) * 1);

	if (!cylinder)
		return (*code = 1, NULL);
	if (skip_till_number(s, 2))
		*code = 3;
	else if (get_coord(&cylinder->coord, s))
		*code = 1;
	else if (skip_till_number(s, 0))
		*code = 3;
	else if (get_vec(&cylinder->vec, s))
		*code = 1;
	else if (skip_till_number(s, 0))
		*code = 3;
	cylinder->diameter = ft_atof(s);
	if (cylinder->diameter < 0.00)
		return (free(cylinder),
			printf("Error: Cylinders diameter value < 0.0\n"), *code = 1, NULL);
	if (*code)
	{
		if (*code == 1)
			printf("\tCylinders problems\n");
		return (free(cylinder), NULL);
	}
	return (cylinder);
}

int	get_cylinder(t_cylinder **head, char **const restrict s)
{
	const int			code = 0;
	t_cylinder *const	cylinder = create_cylinder(s, &(*(int *)&code));

	if (!cylinder)
		return (code);
	set_spherical_object(cylinder, CYLINDER);
	if (skip_till_number(s, 0))
		return (free(cylinder), 3);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->radius_squared = cylinder->radius * cylinder->radius;
	cylinder->height = ft_atof(s);
	if (cylinder->height < 0.00)
		return (free(cylinder),
			printf("Error: Cylinders height value < 0.0\n"), 1);
	if (skip_till_number(s, 0))
		return (free(cylinder), 3);
	if (get_rgb(&cylinder->rgb_save, s))
		return (free(cylinder), printf("\tCylinders problems\n"), 1);
	if (get_material(&cylinder->material, s))
		return (3);
	cylinder->color = argb_to_rgbf(cylinder->rgb_save);
	cylinder->next = *head;
	*head = cylinder;
	if (!**s)
		return (2);
	return (skip_whitespace_hashtag(s, &(__get_all()->line_count)));
}
