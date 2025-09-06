/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:06:36 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:07:02 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "tri_lib.h"

void	_init_canvas(t_all *all)
{
	all->canvas.size_y = 2 * tan((all->camera.fov * (PI_DEFINED / 180)) / 2);
	all->canvas.unit = all->canvas.size_y / (double)all->win_height;
	all->canvas.size_x = all->win_width * all->canvas.unit;
	all->canvas.pix_y[0] = -(all->canvas.size_y / 2);
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

void	_cal_rays_ext(t_all *all, int i, int *j)
{
	all->canvas.rays_save[i][*j].start = all->camera.viewpoint;
	all->canvas.rays[i][*j] = all->canvas.rays_save[i][*j];
	++(*j);
}

void	cal_rays(t_all *all)
{
	int		i;
	int		j;
	t_vec	dir_x;
	t_vec	dir_y;

	i = 0;
	while (i < all->win_height)
	{
		j = 0;
		scalar_multiplication(&all->camera.dir_y, all->canvas.pix_y[i], &dir_y);
		while (j < all->win_width)
		{
			scalar_multiplication(&all->camera.dir_x,
				all->canvas.pix_x[j], &dir_x);
			add_vectors(&all->camera.dir, &dir_x,
				&all->canvas.rays_save[i][j].dir);
			add_vectors(&all->canvas.rays_save[i][j].dir,
				&dir_y, &all->canvas.rays_save[i][j].dir);
			norm_vectors(&all->canvas.rays_save[i][j].dir,
				vec_magnitude(&all->canvas.rays_save[i][j].dir),
				&all->canvas.rays_save[i][j].dir);
			_cal_rays_ext(all, i, &j);
		}
		++i;
	}
}

void	reset_rays(t_all *all)
{
	int		i;
	int		j;

	i = 0;
	while (i < all->win_height)
	{
		j = 0;
		while (j < all->win_width)
		{
			all->canvas.rays_save[i][j].start = all->camera.viewpoint;
			all->canvas.rays[i][j] = all->canvas.rays_save[i][j];
			++j;
		}
		++i;
	}
}
