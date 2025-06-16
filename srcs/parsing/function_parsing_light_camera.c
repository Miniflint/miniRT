#include "miniRT.h"

int	get_ambient_light(t_amb_light *a_light, char **s)
{
	if (a_light->nb > 0)
		return (printf("Error: too much ambient lights\n"), 1);
	a_light->nb = 1;
	if (skip_till_number(s, 1))
		return (3);
	a_light->ratio = ft_atof(s);
	if (a_light->ratio < 0.0 || a_light->ratio > 1.0)
		return (printf("Error: ambient light ratio value < 0.0 || > 1.0\n"), 1);
	printf("%c\n", **s);
	if (skip_till_number(s, 0))
		return (3);
	if (get_rgb(&a_light->rgb, s))
		return (printf("\nAmbient light problem\n"), 1);
	if (!**s)
		return (2);
	return (skip_whitespace_hashtag(s));
}

int	get_camera(t_cam *camera, char **s)
{
	if (camera->nb > 0)
		return (printf("Error: too much camera viewpoint\n"), 1);
	camera->nb = 1;
	if (skip_till_number(s, 1))
		return (3);
	if (get_coord(&camera->viewpoint, s))
		return (printf("\tCamera problem\n"), 1);
	if (skip_till_number(s, 0))
		return (3);
	if (get_vec(&camera->vec, s))
		return (printf("\tCamera problem\n"), 1);
	if (skip_till_number(s, 0))
		return (3);
	camera->fov = ft_atof(s);
	if (camera->fov < 0.0 || camera->fov > 180.0)
		return (printf("Error: camera fov < 0.0 || > 180.0\n"), 1);
	if (!**s)
		return (2);
	return (skip_whitespace_hashtag(s));
}

int	get_light(t_light **head, char **s)
{
	t_light	*light;

	light = (t_light *)create_empty_node(sizeof(t_light) * 1);
	if (!light)
		return (1);
	if (skip_till_number(s, 2))
		return (free(light), 3);
	if (get_coord(&light->coord, s))
		return (free(light), printf("\tLights problems\n"), 1);
	if (skip_till_number(s, 0))
		return (free(light), 3);
	light->ratio = ft_atof(s);
	if (light->ratio < 0.0 || light->ratio > 1.0)
		return (free(light),
			printf("Error: lights ratio value < 0.0 || > 1.0\n"), 1);
	if (skip_till_number(s, 0))
		return (free(light), 3);
	if (get_rgb(&light->rgb, s))
		return (free(light), printf("\tLights problems\n"), 1);
	light->next = *head;
	*head = light;
	if (!**s)
		return (2);
	return (skip_whitespace_hashtag(s));
}
