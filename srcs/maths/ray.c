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
	double	a;
	double	b;
	double	c;

	r = sphere->diameter;
	sub_vectors(O, &sphere->coord, &CO);
	a = dot_product(D, D);
	b = 2 * dot_product(&CO, D);
	c = dot_product(&CO, &CO) - (r*r);
	
	double disciminant = b*b - 4*a*c;
	if (disciminant < 0)
	{
		*t1 = INFINITY;
		*t2 = INFINITY;
		return ;
	}
	*t1 = (-b + sqrt(disciminant)) / (2 * a);
	*t2 = (-b - sqrt(disciminant)) / (2 * a);
}


unsigned int	traceray(t_ray *ray, t_all *all)
{
	double		t1, t2;
	t_sphere	*sphere;
	t_sphere	*closest;
	double		closest_t;

	closest_t = INFINITY;
	closest = NULL;
	sphere = all->spheres;
	while (sphere)
	{
		IntersectRaySphere(&ray->dir, &ray->start, sphere, &t1, &t2);
		if (!isinf(t1) && t1 < closest_t && t1 > 1)
		{
			closest_t = t1;
			closest = sphere;
		}
		if (!isinf(t2) && t2 < closest_t && t2 > 1)
		{
			closest_t = t2;
			closest = sphere;
		}
		sphere = sphere->next;
	}
	if (!isinf(closest_t))
		ray->color = closest->rgb;
	return (TRI_OPAQUE_UNSIGNED | ray->color.r << 16 | ray->color.g << 8 | ray->color.b);
}

void start_rays(t_all *all)
{
	int i;
	int j;
	int	real_i;
	int	real_j;
	int	mi_pix;
	t_tri_lib *lib;

	lib = tri_lib();
	mi_pix = all->canvas.pixel_values / 2;
	i = mi_pix;
	real_i = 0;
	while (real_i < all->win_height)
	{
		real_j = 0;
		j = mi_pix;
		if (i >= all->win_height)
			i = all->win_height - 1;
		while (real_j < all->win_width)
		{
			if (j >= all->win_width)
				j = all->win_width - 1;
			_replace_sized_pixel_on_render(&lib->_windows->_base_render._render, traceray(&all->canvas.rays[i][j], all), real_j, real_i, all->canvas.pixel_values);
			real_j += all->canvas.pixel_values;
			j = real_j + mi_pix;
		}
		real_i += all->canvas.pixel_values;
		i = real_i + mi_pix;
	}
	lib->draw_windows();
}
	//while (j_start < tmp)
	//{
	////column motif
	//i_start = 0;
	//while (i_start < tmp)
	//{
	////motif square space
	//i = i_start;
	//pix_y_base = -((all->win_height >> 1) * unit);
	//pix_x_base = -((all->win_width >> 1) * unit);
	//pix_y = pix_y_base + i * unit;
	//while (i < all->win_height)
	//{
	//	j = j_start;
	//	scalar_multiplication(&all->camera.dir_y, pix_y, &dir_y);
	//	pix_x = pix_x_base + j * unit;
	//	while (j < all->win_width)
	//	{
	//		scalar_multiplication(&all->camera.dir_x, pix_x, &dir_x);
	//		add_vectors(&all->camera.dir, &dir_x, &ray);
	//		add_vectors(&ray, &dir_y, &ray);
	//		color = traceray(&ray, all);
	//		lib->replace_pixel_on_window(lib->_windows, color, j, i);
	//		j += tmp;
	//		pix_x += unit * tmp;
	//	}
	//	pix_y += unit * tmp;
	//	i += tmp;
	//}
	////end motif square space
	//i_start++;
	//}
	////end column motif
	//lib->draw_windows();
	//j_start++;
	//}
	////end line motif
//
//}
