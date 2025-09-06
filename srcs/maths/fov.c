/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:06:38 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:07:01 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	cal_fov(t_all *all)
{
	int				i;
	int				j;
	double			start_pix_x;
	t_argb			color;

	_init_canvas(all);
	start_pix_x = -(all->canvas.size_x / 2);
	i = 1;
	while (i < all->win_height)
	{
		color = mix_colors_normal((t_argb){1
				- (i * ((double)1 / all->win_height)), 0x00, 0x00, 0x00},
				(t_argb){0, 0x77, 0x99, 0xFF});
		all->canvas.pix_x[0] = start_pix_x;
		j = 1;
		while (j < all->win_width)
		{
			all->canvas.pix_x[j] = all->canvas.pix_x[j - 1] + all->canvas.unit;
			all->canvas.rays_save[i][j].color = color;
			++j;
		}
		all->canvas.pix_y[i] = all->canvas.pix_y[i - 1] + all->canvas.unit;
		++i;
	}
	cal_rays(all);
}
