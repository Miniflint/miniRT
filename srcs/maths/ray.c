#include "miniRT.h"
#include "tri_lib.h"

void make_perpendicular(t_cam *cam)
{
	t_vec	ideal_up;
	
	ideal_up = (t_vec){.x = 0, .y = 1, .z = 0};

	if (fabs(dot_product(&cam->dir, &ideal_up)) > 0.9999f)
		ideal_up = (t_vec){.x = 1, .y = 0, .z = 0};
	cross_product(&cam->dir, &ideal_up, &cam->dir_y);
	cross_product(&cam->dir, &cam->dir_y, &cam->dir_x);
}

	// printf("\tdir Vec: (%f,%f,%f)\n",
	// 	all->camera.dir.x, all->camera.dir.y, all->camera.dir.z);
	// printf("\tdir_x Vec: (%f,%f,%f)\n",
	// 	all->camera.dir_x.x, all->camera.dir_x.y, all->camera.dir_x.z);
	// printf("\tdir_y Vec: (%f,%f,%f)\n",
	// 	all->camera.dir_y.x, all->camera.dir_y.y, all->camera.dir_y.z);
	// printf("dot dir  dirx: %f\n", dot_product(&(all->camera.dir), &(all->camera.dir_x)));
	// printf("dot dir  diry: %f\n", dot_product(&(all->camera.dir), &(all->camera.dir_y)));
	// printf("dot dirx diry: %f\n", dot_product(&(all->camera.dir_x), &(all->camera.dir_y)));

void	IntersectRaySphere(t_vec *D, t_vec *O, t_sphere *sphere, double *t1, double *t2)
{
	double	r;
	t_vec	CO;
	double a, b, c;

	r = sphere->diameter;
	sub_vectors(O, &sphere->coord, &CO);
	a = dot_product(D, D);
	b = 2*dot_product(&CO, D);
	c = dot_product(&CO, &CO) - (r*r);
	
	double disciminant = b*b - 4*a*c;
	if (disciminant < 0)
	{
		*t1 = NAN;
		*t2 = NAN;
		return ;
	}
	*t1 = (-b + sqrt(disciminant)) / (2*a);
	*t2 = (-b - sqrt(disciminant)) / (2*a);
}


unsigned int	traceray(t_vec *ray, t_all *all)
{
	double		t1, t2;
	t_sphere	*sphere;
	t_sphere	*closest;
	double		closest_t;
	unsigned int	argb;

	closest_t = NAN;
	sphere = all->spheres;
	while (sphere)
	{
		IntersectRaySphere(ray, &all->camera.viewpoint, sphere, &t1, &t2);
		if (!isnan(t1) && t1 < closest_t && t1 > 1)
		{
			closest_t = t1;
			closest = sphere;
		}
		if (!isnan(t2) && t2 < closest_t && t2 > 1)
		{
			closest_t = t2;
			closest = sphere;
		}
		sphere = sphere->next;
	}
	argb = 0xFF000000;
	argb += closest->rgb.r << 16;
	argb += closest->rgb.g << 8;
	argb += closest->rgb.b;
	if (!isnan(t1) && !isnan(t2))
		return (argb);
	return (0xFFFFFFFF);
}

void start_rays(t_all *all)
{
	int i = 0;
	int j;
	double pix_x;
	double pix_y;
	t_vec	ray;
	t_vec	dir_x;
	t_vec	dir_y;
	t_tri_lib *lib;

	lib = tri_lib();
	make_perpendicular(&(all->camera));
	while (i < all->win_height)
	{
		j = 0;
		pix_y = all->canvas.size_y / 2 - (((double)i / (double)all->win_height) * all->canvas.size_y);
		scalar_multiplication(&all->camera.dir_y, pix_y, &dir_y);
		while (j < all->win_width)
		{
			pix_x = all->canvas.size_x / 2 - (((double)j / (double)all->win_width) * all->canvas.size_x);
			scalar_multiplication(&all->camera.dir_x, pix_x, &dir_x);
			add_vectors(&all->camera.dir, &dir_x, &ray);
			add_vectors(&ray, &dir_y, &ray);
			lib->replace_pixel_on_window(lib->_windows, traceray(&ray, all), j, i);
			j += 1;
		}
		i += 1;
	}
}
