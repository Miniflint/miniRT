#include "miniRT.h"
#include "tri_lib.h"

void cal_fov(t_all *all)
{
	int		i;
	int		j;
	double	start_pix_x;

	all->canvas.size_y = 2 * tan((all->camera.fov * (PI_DEFINED / 180)) / 2);
	all->canvas.unit = all->canvas.size_y / (double)all->win_height;
	all->canvas.size_x = all->win_width * all->canvas.unit;
	all->canvas.pix_y[0] = -(all->canvas.size_y / 2);
	start_pix_x = -(all->canvas.size_x / 2);
	i = 1;
	while (i < all->win_height)
	{
		all->canvas.pix_x[0] = start_pix_x;
		j = 1;
		while (j < all->win_width)
		{
			all->canvas.pix_x[j] = all->canvas.pix_x[j - 1] + all->canvas.unit;
			++j;
		}
		all->canvas.pix_y[i] = all->canvas.pix_y[i - 1] + all->canvas.unit;
		++i;
	}
}

void	init_start_ray(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while (i < all->win_height)
	{
		j = 0;
		while (j < all->win_width)
			all->canvas.rays[i][j++].start = all->camera.viewpoint;
		++i;
	}
}

void cal_rays(t_all *all)
{
	int 	i;
	int 	j;
	t_vec	dir_x;
	t_vec	dir_y;
	t_argb	color;

	
	i = 0;
	while (i < all->win_height)
	{
		j = 0;
		scalar_multiplication(&all->camera.dir_y, all->canvas.pix_y[i], &dir_y);
		color = mix_colors_normal((t_argb){1 - (i * ((double)1 / all->win_height)), 0x00, 0x00, 0x00}, unsigned_to_argb(0x007799FF));
		while (j < all->win_width)
		{
			scalar_multiplication(&all->camera.dir_x, all->canvas.pix_x[j], &dir_x);
			add_vectors(&all->camera.dir, &dir_x, &all->canvas.rays[i][j].dir);
			add_vectors(&all->canvas.rays[i][j].dir, &dir_y, &all->canvas.rays[i][j].dir);
			all->canvas.rays[i][j].start = all->camera.viewpoint;
			all->canvas.rays[i][j].color = color;
			++j;
		}
		++i;
	}
}
