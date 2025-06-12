#include "miniRT.h"

int get_rgb(t_rgb *rgb, char **s)
{
    const t_minuint   max_rgb_val = 255;
    unsigned int        real_value;

    real_value = ft_atoi(s);
    if (*((*s)++) != ',')
        return (printf("Error while trying to decode (R)GB color @: %c\n", *((*s) - 1)), 1);
    if (real_value > max_rgb_val)
        return (printf("Error: (R)GB value < 0 || > 255\n"), 1);
    rgb->r = real_value;
    real_value = ft_atoi(s);
    if (*((*s)++) != ',')
        return (printf("Error while trying to decode R(G)B color @: %c\n", *((*s) - 1)), 1);
    if (real_value > max_rgb_val)
        return (printf("Error: R(G)B value < 0 || > 255\n"), 1);
    rgb->g = real_value;
    real_value = ft_atoi(s);
    if (**s && !ft_iswhitespace(**s))
        return (printf("Error while trying to decode RG(B) color @: %c\n", **s), 1);
    if (real_value > max_rgb_val)
        return (printf("Error: RG(B) value < 0 || > 255\n"), 1);
    rgb->b = real_value;
    return (0);
}

int get_coord(t_coord *coord, char **s)
{
    coord->x = ft_atof(s);
    if (*((*s)++) != ',')
        return (printf("Error while trying to decode (X)YZ color @: %c\n", *((*s) - 1)), 1);
    coord->y = ft_atof(s);
    if (*((*s)++) != ',')
        return (printf("Error while trying to decode X(Y)Z color @: %c\n", *((*s) - 1)), 1);
    coord->z = ft_atof(s);
    if (**s && !ft_iswhitespace(**s))
        return (printf("Error while trying to decode XY(Z) color @: %c\n", **s), 1);
    return (0);
}

int get_vec(t_vec *vec, char **s)
{
    vec->x = ft_atof(s);
    if (*((*s)++) != ',')
        return (printf("Error while trying to decode (X)YZ color @: %c\n", *((*s) - 1)), 1);
    if (vec->x > 1.0 || vec->x < -1.0)
        return (printf("Error: (X)YZ value < -1.0 || > 1.0\n"), 1);
    vec->y = ft_atof(s);
    if (*((*s)++) != ',')
        return (printf("Error while trying to decode X(Y)Z color @: %c\n", *((*s) - 1)), 1);
    if (vec->y > 1.0 || vec->y < -1.0)
        return (printf("Error: X(Y)Z value < -1.0 || > 1.0\n"), 1);
    vec->z = ft_atof(s);
    if (**s && !ft_iswhitespace(**s))
        return (printf("Error while trying to decode XY(Z) color @: %c\n", **s), 1);
    if (vec->z > 1.0 || vec->z < -1.0)
        return (printf("Error: XY(Z) value < -1.0 || > 1.0\n"), 1);
    return (0);
}

int get_ambient_light(t_amb_light *a_light, char **s)
{
    skip_till_number(s);
    a_light->ratio = ft_atof(s);
    if (a_light->ratio < 0.0 || a_light->ratio > 1.0)
        return (printf("Error: ratio value < 0.0 || > 1.0\n"), 1);
    skip_till_number(s);
    if (get_rgb(&a_light->rgb, s))
        return (1);
    if (!**s)
        return (2);
    return (skip_whitespace_hashtag(s));
}


int get_camera(t_cam *camera, char **s)
{
    skip_till_number(s);
    if (get_coord(&camera->viewpoint, s))
        return (1);
    skip_till_number(s);
    if (get_vec(&camera->vec, s))
        return (1);
    skip_till_number(s);
    camera->fov = ft_atof(s);
    if (camera->fov < 0.0 || camera->fov > 180.0)
        return (printf("Error: camera fov < 0.0 || > 180.0\n"), 1);
    if (!**s)
        return (2);
    return (skip_whitespace_hashtag(s));
}


int get_light(t_light *light, char **s, t_light **head)
{
    skip_till_number(s);
    if (get_coord(&light->coord, s))
        return (1);
    light->ratio = ft_atof(s);
    if (light->ratio < 0.0 || light->ratio > 1.0)
        return (printf("Error: ratio value < 0.0 || > 1.0\n"), 1);
    if (get_rgb(&light->rgb, s))
        return (1);
    light->next = *head;
    *head = light;
    if (!**s)
        return (2);
    return (skip_whitespace_hashtag(s));
}

int get_sphere(t_sphere *sphere, char **s, t_sphere **head)
{
    skip_till_number(s);
    if (get_coord(&sphere->coord, s))
        return (1);
    sphere->diameter = ft_atof(s);
    if (sphere->diameter < 0.00)
        return (printf("Error: diameter value < 0.0\n"), 1);
    if (get_rgb(&sphere->rgb, s))
        return (1);
    sphere->next = *head;
    *head = sphere;
    if (!**s)
        return (2);
    return (skip_whitespace_hashtag(s));
}

int get_plane(t_plane *plane, char **s, t_plane **head)
{
    skip_till_number(s);
    if (get_coord(&plane->coord, s))
        return (1);
    if (get_vec(&plane->vec, s))
        return (1);
    if (get_rgb(&plane->rgb, s))
        return (1);
    plane->next = *head;
    *head = plane;
    if (!**s)
        return (2);
    return (skip_whitespace_hashtag(s));
}

int get_cylinder(t_cylinder *cylinder, char **s, t_cylinder **head)
{
    skip_till_number(s);
    if (get_coord(&cylinder->coord, s))
        return (1);
    if (get_vec(&cylinder->vec, s))
        return (1);
    cylinder->diameter = ft_atof(s);
    if (cylinder->diameter < 0.00)
        return (printf("Error: diameter value < 0.0\n"), 1);
    cylinder->height = ft_atof(s);
    if (cylinder->height < 0.00)
        return (printf("Error: height value < 0.0\n"), 1);
    if (get_rgb(&cylinder->rgb, s))
        return (1);
    cylinder->next = *head;
    *head = cylinder;
    if (!**s)
        return (2);
    return (skip_whitespace_hashtag(s));
}