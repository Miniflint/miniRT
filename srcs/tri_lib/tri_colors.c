/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 03:09:22 by hermesrolle       #+#    #+#             */
/*   Updated: 2025/09/06 17:24:49 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_colors.h"

t_argb	mix_colors_normal(t_argb top, t_argb base)
{
	if (top.a >= 1.0000)
		return (top);
	if (top.a <= 0.0000)
		return (base);
	base.r = top.r * top.a + base.r * (1.0 - top.a);
	base.g = top.g * top.a + base.g * (1.0 - top.a);
	base.b = top.b * top.a + base.b * (1.0 - top.a);
	base.a = top.a + base.a * (1.0 - top.a);
	return (base);
}

unsigned int	mix_colors_normal_u_no_a(t_argb top, t_argb base)
{
	if (top.a >= 1.0000)
		return ((top.r << 16) | (top.g << 8) | top.b);
	if (top.a <= 0.0000)
		return ((base.r << 16) | (base.g << 8) | base.b);
	base.r = top.r * top.a + base.r * (1.0 - top.a);
	base.g = top.g * top.a + base.g * (1.0 - top.a);
	base.b = top.b * top.a + base.b * (1.0 - top.a);
	return ((base.r << 16) | (base.g << 8) | base.b);
}

unsigned int	_mix_colors_render_to_render(t_argb top, t_argb base)
{
	if (top.a >= 1.0000)
		return ((top.r << 16) | (top.g << 8) | top.b);
	if (top.a <= 0.0000)
		return ((base.r << 16) | (base.g << 8) | base.b);
	base.r = top.r + base.r * (1.0 - top.a);
	base.g = top.g + base.g * (1.0 - top.a);
	base.b = top.b + base.b * (1.0 - top.a);
	return ((base.r << 16) | (base.g << 8) | base.b);
}

unsigned int	mix_colors_normal_u(t_argb top, t_argb base)
{
	if (top.a >= 1.0000)
		return (argb_to_unsigned(top));
	if (top.a <= 0.0000)
		return (argb_to_unsigned(base));
	base.r = top.r * top.a + base.r * (1.0 - top.a);
	base.g = top.g * top.a + base.g * (1.0 - top.a);
	base.b = top.b * top.a + base.b * (1.0 - top.a);
	base.a = top.a + base.a * (1.0 - top.a);
	return (argb_to_unsigned(base));
}

t_rgb_f	clamp_rgb_f(t_rgb_f color)
{
	if (color.r > 1.0)
		color.r = 1.0;
	if (color.g > 1.0)
		color.g = 1.0;
	if (color.b > 1.0)
		color.b = 1.0;
	return (color);
}
