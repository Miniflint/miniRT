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

	r = sphere->diameter / 2;
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


unsigned int	traceray(t_vec *ray, t_all *all)
{
	double		t1, t2;
	t_sphere	*sphere;
	t_sphere	*closest;
	double		closest_t;
	unsigned int	argb;

	closest_t = INFINITY;
	closest = NULL;
	sphere = all->spheres;
	while (sphere)
	{
		IntersectRaySphere(ray, &all->camera.viewpoint, sphere, &t1, &t2);
		if (!isinf(t1) && t1 < closest_t && t1 > 0.1)
		{
			closest_t = t1;
			closest = sphere;
		}
		if (!isinf(t2) && t2 < closest_t && t2 > 0.1)
		{
			closest_t = t2;
			closest = sphere;
		}
		sphere = sphere->next;
	}
	argb = 0xFF000000;
	if (!isinf(closest_t))
	{
		argb += closest->rgb.r << 16;
		argb += closest->rgb.g << 8;
		argb += closest->rgb.b;
	}
	return (argb);
}

void start_rays(t_all *all)
{
	int i;
	int j;
	int i_start;
	int j_start;
	const int tmp = 10;
	double pix_x;
	double pix_x_base;
	double pix_y_base;
	double pix_y;
	t_vec	ray;
	t_vec	dir_x;
	t_vec	dir_y;
	t_tri_lib *lib;
	double	unit;
	unsigned int color;

	lib = tri_lib();
	unit = all->canvas.size_y / (double)all->win_width;
	make_perpendicular(&(all->camera));
	//line motif
	j_start = 0;
	while (j_start < tmp)
	{
	//column motif
	i_start = 0;
	while (i_start < tmp)
	{
	//motif square space
	i = i_start;
	pix_y_base = -((all->win_height / 2) * unit);
	pix_x_base = -((all->win_width >> 1) * unit);
	pix_y = pix_y_base + i * unit;
	while (i < all->win_height)
	{
		j = j_start;
		scalar_multiplication(&all->camera.dir_y, pix_y, &dir_y);
		pix_x = pix_x_base + j * unit;
		while (j < all->win_width)
		{
			scalar_multiplication(&all->camera.dir_x, pix_x, &dir_x);
			add_vectors(&all->camera.dir, &dir_x, &ray);
			add_vectors(&ray, &dir_y, &ray);
			color = traceray(&ray, all);
			lib->replace_pixel_on_window(lib->_windows, color, j, i);
			j += tmp;
			pix_x += unit * tmp;
		}
		pix_y += unit * tmp;
		i += tmp;
	}
	lib->draw_windows();
	//end motif square space
	i_start++;
	}
	//end column motif
	j_start++;
	}
	//end line motif

}
