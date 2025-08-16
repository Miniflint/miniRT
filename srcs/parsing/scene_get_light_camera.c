#include "miniRT.h"

int	get_ambient_light(t_amb_light *a_light, char **const restrict s)
{
	if (a_light->nb > 0)
		return (printf("Error: too much ambient lights\n"), 1);
	a_light->nb = 1;
	if (skip_till_number(s, 1))
		return (3);
	a_light->ratio = ft_atof(s);
	if (a_light->ratio < 0.0 || a_light->ratio > 1.0)
		return (printf("Error: ambient light ratio value < 0.0 || > 1.0\n"), 1);
	if (skip_till_number(s, 0))
		return (3);
	if (get_rgb(&a_light->rgb, s))
		return (printf("\nAmbient light problem\n"), 1);
	if (!**s)
		return (2);
	a_light->rgb_norm = (t_rgb_norm){
		.r=((double)a_light->rgb.r / 255.0) * a_light->ratio,
		.g=((double)a_light->rgb.g / 255.0) * a_light->ratio,
		.b=((double)a_light->rgb.b / 255.0) * a_light->ratio
	};
	return (skip_whitespace_hashtag(s, &(__get_all()->line_count)));
}

int	get_camera(t_cam *camera, char **const restrict s)
{
	if (camera->nb > 0)
		return (printf("Error: too much camera viewpoint\n"), 3);
	camera->nb = 1;
	if (skip_till_number(s, 1))
		return (3);
	if (get_coord(&camera->viewpoint, s))
		return (printf("\tCamera problem\n"), 1);
	if (skip_till_number(s, 0))
		return (3);
	if (get_vec(&camera->dir, s))
		return (printf("\tCamera problem\n"), 1);
	if (skip_till_number(s, 0))
		return (3);
	camera->fov = ft_atof(s);
	if (camera->fov <= 0.0 || camera->fov > 180.0)
		return (printf("Error: camera fov < 0.0 || > 180.0\n"), 3);
	if (!**s)
		return (2);
	return (skip_whitespace_hashtag(s, &(__get_all()->line_count)));
}

int	get_light(t_light **head, char **const restrict s)
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
	light->rgb_norm = (t_rgb_norm){
		.r=((double)light->rgb.r / 255.0),
		.g=((double)light->rgb.g / 255.0),
		.b=((double)light->rgb.b / 255.0)
	};
	return (skip_whitespace_hashtag(s, &(__get_all()->line_count)));
}
