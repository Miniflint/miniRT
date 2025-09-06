/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:05:45 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:06:12 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	apply_argb_save_rgb(t_rgb *rgb_save, t_rgb_f ambient_rgb, t_rgb *into)
{
	into->r = (double)rgb_save->r * ambient_rgb.r;
	into->g = (double)rgb_save->g * ambient_rgb.g;
	into->b = (double)rgb_save->b * ambient_rgb.b;
}

void	apply_rgb_all_shape(t_all *all)
{
	const t_sphere		*tmp_sp = all->spheres;
	const t_plane		*tmp_pl = all->planes;
	const t_cylinder	*tmp_cy = all->cylinders;
	const t_rgb_f		r = all->ambient_light.rgb_norm;

	while (all->spheres)
	{
		apply_argb_save_rgb(&all->spheres->rgb_save, r, &all->spheres->rgb);
		all->spheres = all->spheres->next;
	}
	all->spheres = (t_sphere *)tmp_sp;
	while (all->planes)
	{
		apply_argb_save_rgb(&all->planes->rgb_save, r, &all->planes->rgb);
		all->planes = all->planes->next;
	}
	all->planes = (t_plane *)tmp_pl;
	while (all->cylinders)
	{
		apply_argb_save_rgb(&all->cylinders->rgb_save, r, &all->cylinders->rgb);
		all->cylinders = all->cylinders->next;
	}
	all->cylinders = (t_cylinder *)tmp_cy;
}
