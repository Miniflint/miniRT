#include "miniRT.h"

int get_rgb(t_rgb *rgb, char **s)
{
    const t_minuint   max_rgb_val = 255;
    unsigned int        real_value;

    real_value = ft_atoi(s);
    if (*((*s)++) != ',')
        return (printf("Error while trying to decode (R)GB color @: [%d|%c]\n", *((*s) - 1), *((*s) - 1)), 1);
    if (real_value > max_rgb_val)
        return (printf("Error: (R)GB value < 0 || > 255\n"), 1);
    rgb->r = real_value;
    real_value = ft_atoi(s);
    if (*((*s)++) != ',')
        return (printf("Error while trying to decode R(G)B color @: [%d|%c]\n", *((*s) - 1), *((*s) - 1)), 1);
    if (real_value > max_rgb_val)
        return (printf("Error: R(G)B value < 0 || > 255\n"), 1);
    rgb->g = real_value;
    real_value = ft_atoi(s);
    if (**s && !ft_iswhitespace(**s))
        return (printf("Error while trying to decode RG(B) color @: [%d|%c]\n", **s, **s), 1);
    if (real_value > max_rgb_val)
        return (printf("Error: RG(B) value < 0 || > 255\n"), 1);
    rgb->b = real_value;
    return (0);
}

int get_coord(t_coord *coord, char **s)
{
    coord->x = ft_atof(s);
    if (*((*s)++) != ',')
        return (printf("Error while trying to decode (X)YZ coordinates @: [%d|%c]\n", *((*s) - 1), *((*s) - 1)), 1);
    coord->y = ft_atof(s);
    if (*((*s)++) != ',')
        return (printf("Error while trying to decode X(Y)Z coordinates @: [%d|%c]\n", *((*s) - 1), *((*s) - 1)), 1);
    coord->z = ft_atof(s);
    if (**s && !ft_iswhitespace(**s))
        return (printf("Error while trying to decode XY(Z) coordinates @: [%d|%c]\n", **s, **s), 1);
    return (0);
}

int get_vec(t_vec *vec, char **s)
{
    vec->x = ft_atof(s);
    if (*((*s)++) != ',')
        return (printf("Error while trying to decode (X)YZ coordinates @: [%d|%c]\n", *((*s) - 1), *((*s) - 1)), 1);
    if (vec->x > 1.0 || vec->x < -1.0)
        return (printf("Error: (X)YZ value < -1.0 || > 1.0\n"), 1);
    vec->y = ft_atof(s);
    if (*((*s)++) != ',')
        return (printf("Error while trying to decode X(Y)Z coordinates @: [%d|%c]\n", *((*s) - 1), *((*s) - 1)), 1);
    if (vec->y > 1.0 || vec->y < -1.0)
        return (printf("Error: X(Y)Z value < -1.0 || > 1.0\n"), 1);
    vec->z = ft_atof(s);
    if (**s && !ft_iswhitespace(**s))
        return (printf("Error while trying to decode XY(Z) coordinates @: [%d|%c]\n", **s, **s), 1);
    if (vec->z > 1.0 || vec->z < -1.0)
        return (printf("Error: XY(Z) value < -1.0 || > 1.0\n"), 1);
    return (0);
}

int get_ambient_light(t_amb_light *a_light, char **s)
{
    if (a_light->nb > 0)
        return (printf("Error: too much ambient lights\n"), 1);
    a_light->nb = 1;
    if(skip_till_number(s, 1))
        return (3);
    a_light->ratio = ft_atof(s);
    if (a_light->ratio < 0.0 || a_light->ratio > 1.0)
        return (printf("Error: ambient light ratio value < 0.0 || > 1.0\n"), 1);
    printf("%c\n", **s);
    if(skip_till_number(s, 0))
        return (3);
    if (get_rgb(&a_light->rgb, s))
        return (printf("\nAmbient light problem\n"), 1);
    if (!**s)
        return (2);
    return (skip_whitespace_hashtag(s));
}


int get_camera(t_cam *camera, char **s)
{
    if (camera->nb > 0)
        return (printf("Error: too much camera viewpoint\n"), 1);
    camera->nb = 1;
    if(skip_till_number(s, 1))
        return (3);
    if (get_coord(&camera->viewpoint, s))
        return (printf("\tCamera problem\n"), 1);
    if(skip_till_number(s, 0))
        return (3);
    if (get_vec(&camera->vec, s))
        return (printf("\tCamera problem\n"), 1);
    if(skip_till_number(s, 0))
        return (3);
    camera->fov = ft_atof(s);
    if (camera->fov < 0.0 || camera->fov > 180.0)
        return (printf("Error: camera fov < 0.0 || > 180.0\n"), 1);
    if (!**s)
        return (2);
    return (skip_whitespace_hashtag(s));
}


int get_light(t_light **head, char **s)
{
    t_light *light;
    
    light = (t_light *)create_empty_node(sizeof(t_light) * 1);
    if (!light)
        return (1);
    if(skip_till_number(s, 2))
        return (free(light), 3);
    if (get_coord(&light->coord, s))
        return (free(light), printf("\tLights problems\n"), 1);
    if(skip_till_number(s, 0))
        return (free(light), 3);
    light->ratio = ft_atof(s);
    if (light->ratio < 0.0 || light->ratio > 1.0)
        return (free(light), printf("Error: lights ratio value < 0.0 || > 1.0\n"), 1);
    if(skip_till_number(s, 0))
        return (free(light), 3);
    if (get_rgb(&light->rgb, s))
        return (free(light), printf("\tLights problems\n"), 1);
    light->next = *head;
    *head = light;
    if (!**s)
        return (2);
    return (skip_whitespace_hashtag(s));
}

int get_sphere(t_sphere **head, char **s)
{
    t_sphere *sphere;
    
    sphere = (t_sphere *)create_empty_node(sizeof(t_sphere) * 1);
    if (!sphere)
        return (1);
    if(skip_till_number(s, 2))
        return (free(sphere), 3);
    if (get_coord(&sphere->coord, s))
        return (free(sphere), printf("\tSpheres problem\n"), 1);
    if(skip_till_number(s, 0))
        return (free(sphere), 3);
    sphere->diameter = ft_atof(s);
    if (sphere->diameter < 0.00)
        return (free(sphere), printf("Error: Spheres diameter value < 0.0\n"), 1);
    if(skip_till_number(s, 0))
        return (free(sphere), 3);
    if (get_rgb(&sphere->rgb, s))
        return (free(sphere), printf("\tSpheres problem\n"), 1);
    sphere->next = *head;
    *head = sphere;
    if (!**s)
        return (2);
    return (skip_whitespace_hashtag(s));
}

int get_plane(t_plane **head, char **s)
{
    t_plane *plane;
    
    plane = (t_plane *)create_empty_node(sizeof(t_plane) * 1);
    if (!plane)
        return (1);
    if(skip_till_number(s, 2))
        return (free(plane), 3);
    if (get_coord(&plane->coord, s))
        return (free(plane), printf("\tPlanes problems\n"), 1);
    if(skip_till_number(s, 0))
        return (free(plane), 3);
    if (get_vec(&plane->vec, s))
        return (free(plane), printf("\tPlanes problems\n"), 1);
    if(skip_till_number(s, 0))
        return (free(plane), 3);
    if (get_rgb(&plane->rgb, s))
        return (free(plane), printf("\tPlanes problems\n"), 1);
    plane->next = *head;
    *head = plane;
    if (!**s)
        return (2);
    return (skip_whitespace_hashtag(s));
}


int get_cylinder(t_cylinder **head, char **s)
{
    t_cylinder *cylinder;
    
    cylinder = (t_cylinder *)create_empty_node(sizeof(t_cylinder) * 1);
    if (!cylinder)
        return (1);
    if(skip_till_number(s, 2))
        return (free(cylinder), 3);
    if (get_coord(&cylinder->coord, s))
        return (free(cylinder), printf("\tCylinders problems\n"), 1);
    if(skip_till_number(s, 0))
        return (free(cylinder), 3);
    if (get_vec(&cylinder->vec, s))
        return (free(cylinder), printf("\tCylinders problems\n"), 1);
    if(skip_till_number(s, 0))
        return (free(cylinder), 3);
    cylinder->diameter = ft_atof(s);
    if (cylinder->diameter < 0.00)
        return (free(cylinder), printf("Error: Cylinders diameter value < 0.0\n"), 1);
    if(skip_till_number(s, 0))
        return (free(cylinder), 3);
    cylinder->height = ft_atof(s);
    if (cylinder->height < 0.00)
        return (free(cylinder), printf("Error: Cylinders height value < 0.0\n"), 1);
    if(skip_till_number(s, 0))
        return (free(cylinder), 3);
    if (get_rgb(&cylinder->rgb, s))
        return (free(cylinder), printf("\tCylinders problems\n"), 1);
    cylinder->next = *head;
    *head = cylinder;
    if (!**s)
        return (2);
    return (skip_whitespace_hashtag(s));
}