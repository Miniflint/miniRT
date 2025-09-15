#include "miniRT.h"

	// t_rgb_f const	color[5] = { //Green
	// 	{0.0156,0.8509,0.2235},
	// 	{0.0117,0.6509,0.2352},
	// 	{0.0078,0.4509,0.2},
	// 	{0.0078,0.3490,0.2235},
	// 	{0.004,0.1372,0.2509}
	// };

t_rgb_f	get_background_color(t_all *all, int i)
{
	double			alpha;
	int				select;
	t_rgb_f const	color[5] = {
	{0.1569, 0.2078, 0.3098},
	{0.2902, 0.3882, 0.5882},
	{0.6, 0.6078, 0.7686},
	{0.9294, 0.6156, 0.5019},
	{0.7098, 0.3725, 0.3412}
	};

	alpha = ((double)i * ((double)4.0 / (double)all->win_height));
	select = alpha;
	if (select >= 4)
		return (color[4]);
	alpha -= (double)select;
	return ((t_rgb_f){
		color[select + 1].r * alpha + color[select].r * (1.0 - alpha),
		color[select + 1].g * alpha + color[select].g * (1.0 - alpha),
		color[select + 1].b * alpha + color[select].b * (1.0 - alpha)});
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
		color = get_background_color(all, i);
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
