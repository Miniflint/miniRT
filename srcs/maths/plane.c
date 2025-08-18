#include "miniRT.h"

// t = n * (r0 - p0) / (n * d)
// t = plane->vec * (ray->start - plane->vec) / plane->vec * ray->dir;

void    intersect_plane(t_plane *plane, t_ray *ray, double *t)
{
    double  dot;
    t_vec   new_vec;

    dot = dot_product(&plane->vec, &ray->dir);
    if (dot == 0)
    {
        *t = INFINITY;
        return ;
    }
    sub_vectors(&ray->start, &plane->coord, &new_vec);
    *t = -dot_product(&plane->vec, &new_vec) / dot;
}
