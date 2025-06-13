#include "miniRT.h"

void free_L(t_light *light)
{
    if (!light)
        return ;
    free_L(light->next);
    free(light);
    light = NULL;
}

void free_sp(t_sphere *sphere)
{
    if (!sphere)
        return ;
    free_sp(sphere->next);
    free(sphere);
    sphere = NULL;
}

void free_pl(t_plane *plane)
{
    if (!plane)
        return ;
    free_pl(plane->next);
    free(plane);
    plane = NULL;
}

void free_cy(t_cylinder *cylinder)
{
    if (!cylinder)
        return ;
    free_cy(cylinder->next);
    free(cylinder);
    cylinder = NULL;
}

void free_all(t_all *all)
{
    free_L(all->lights);
    all->lights = NULL;
    free_sp(all->spheres);
    all->spheres = NULL;
    free_pl(all->planes);
    all->planes = NULL;
    free_cy(all->cylinders);
    all->cylinders = NULL;
}