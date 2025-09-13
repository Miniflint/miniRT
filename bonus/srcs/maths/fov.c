#include "miniRT.h"

t_rgb_f	get_background_color(double alpha, t_rgb_f a, t_rgb_f b)
{
	return ((t_rgb_f){a.r * alpha + b.r * (1.0 - alpha),
		a.g * alpha + b.g * (1.0 - alpha),
		a.b * alpha + b.b * (1.0 - alpha)});
}

void	cal_fov(t_all *all)
{
	int				i;
	int				j;
	double			start_pix_x;
	t_rgb_f			color;

	_init_canvas(all);
	start_pix_x = -(all->canvas.size_x / 2);
	i = 1;
	while (i < all->win_height)
	{
		color = get_background_color(
				1 - (i * ((double)1 / all->win_height)),
				(t_rgb_f){0, 0, 0}, (t_rgb_f){0.05, 0.05, 0.5});
		all->canvas.pix_x[0] = start_pix_x;
		j = 1;
		while (j < all->win_width)
		{
			all->canvas.pix_x[j] = all->canvas.pix_x[j - 1] + all->canvas.unit;
			all->canvas.rays_save[i][j].color = color;
			all->canvas.rays_save[i][j].to_draw = 0;
			++j;
		}
		all->canvas.pix_y[i] = all->canvas.pix_y[i - 1] + all->canvas.unit;
		++i;
	}
	cal_rays(all);
}
