#include "miniRT.h"

void    print_AC(t_amb_light *ambient_light, t_cam *camera)
{
    printf("AMBIENT LIGHT:\n");
    printf("\tRatio: %f\n", ambient_light->ratio);
    printf("\tRGB: %d %d %d\n", ambient_light->rgb.r, ambient_light->rgb.g, ambient_light->rgb.b);
    printf("CAMERA:\n");
    printf("\tViewpoint: %f %f %f\n", camera->viewpoint.x, camera->viewpoint.y, camera->viewpoint.z);
    printf("\tVec: %f %f %f\n", camera->vec.x, camera->vec.y, camera->vec.z);
    printf("\tFOV: %d\n", camera->fov);
}

void print_L(t_light *light, int depth)
{
    if (!light)
        return ;
    if (!depth)
        printf("LIGHTS:\n");
    printf("\tCoord: %f %f %f\n", light->coord.x, light->coord.y, light->coord.z);
    printf("\tRatio: %f\n", light->ratio);
    printf("\tRGB: %d %d %d\n", light->rgb.r, light->rgb.g, light->rgb.b);
    printf("----------------------------------------------------------------------\n");
    print_L(light->next, depth + 1);
}

void print_sp(t_sphere *sphere, int depth)
{
    if (!sphere)
        return ;
    if (!depth)
        printf("SPHERES:\n");
    printf("\tCoord: %f %f %f\n", sphere->coord.x, sphere->coord.y, sphere->coord.z);
    printf("\tDiameter: %f\n", sphere->diameter);
    printf("\tRGB: %d %d %d\n", sphere->rgb.r, sphere->rgb.g, sphere->rgb.b);
    printf("----------------------------------------------------------------------\n");
    print_sp(sphere->next, depth + 1);
}

void print_pl(t_plane *plane, int depth)
{
    if (!plane)
        return ;
    if (!depth)
        printf("PLANES:\n");
    printf("\tCoord: %f %f %f\n", plane->coord.x, plane->coord.y, plane->coord.z);
    printf("\tVec: %f %f %f\n", plane->vec.x, plane->vec.y, plane->vec.z);
    printf("\tRGB: %d %d %d\n", plane->rgb.r, plane->rgb.g, plane->rgb.b);
    printf("----------------------------------------------------------------------\n");
    print_pl(plane->next, depth + 1);
}

void print_cy(t_cylinder *cylinder, int depth)
{
    if (!cylinder)
        return ;
    if (!depth)
        printf("CYLINDERS:\n");
    printf("\tCoord: %f %f %f\n", cylinder->coord.x, cylinder->coord.y, cylinder->coord.z);
    printf("\tDiameter: %f\n", cylinder->diameter);
    printf("\tHeight: %f\n", cylinder->height);
    printf("\tRGB: %d %d %d\n", cylinder->rgb.r, cylinder->rgb.g, cylinder->rgb.b);
    printf("----------------------------------------------------------------------\n");
    print_cy(cylinder->next, depth + 1);
}
