#include "miniRT.h"

	// t_rgb_f const	color[5] = { //Green
	// 	{0.0156,0.8509,0.2235},
	// 	{0.0117,0.6509,0.2352},
	// 	{0.0078,0.4509,0.2},
	// 	{0.0078,0.3490,0.2235},
	// 	{0.004,0.1372,0.2509}
	// };

void	cal_fov(t_all *all)
{
	int				i;
	int				j;
	double			start_pix_x;

	_init_canvas(all);
	start_pix_x = -(all->canvas.size_x / 2);
	i = 1;
	while (i < all->win_height)
	{
		// color = get_background_color(all, i);
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
	cal_rays(all);
}
