/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 03:09:22 by hermesrolle       #+#    #+#             */
/*   Updated: 2025/08/20 08:54:54 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_colors.h"

t_argb	unsigned_to_argb(unsigned int color)
{
	t_argb	argb;

	argb.a = ((color >> 24) & 0xFF) / 255.0;
	argb.r = (color >> 16) & 0xFF;
	argb.g = (color >> 8) & 0xFF;
	argb.b = color & 0xFF;
	return (argb);
}

unsigned int	argb_to_unsigned(t_argb color)
{
	t_color	a;

	a = (t_color)(color.a * 255);
	return ((a << 24) | (color.r << 16) | (color.g << 8) | color.b);
}

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

t_rgb_f	argb_to_rgbf(t_argb color)
{
	return ((t_rgb_f){
		((double)color.r / 255.0),
		((double)color.g / 255.0),
		((double)color.b / 255.0)});
}

t_argb	rgb_f_to_argb(t_rgb_f color)
{
	t_argb	ret;

	ret.a = 1;
	if (color.r >= 1.0)
		ret.r = 255;
	else
		ret.r = 255.0 * color.r + 0.5;
	if (color.g >= 1.0)
		ret.g = 255;
	else
		ret.g = 255.0 * color.g + 0.5;
	if (color.b >= 1.0)
		ret.b = 255;
	else
		ret.b = 255.0 * color.b + 0.5;
	return (ret);
}

unsigned int	rgb_f_to_unsigned(t_rgb_f color)
{
	t_argb	ret;

	if (color.r >= 1.0)
		ret.r = 255;
	else
		ret.r = 255.0 * color.r + 0.5;
	if (color.g >= 1.0)
		ret.g = 255;
	else
		ret.g = 255.0 * color.g + 0.5;
	if (color.b >= 1.0)
		ret.b = 255;
	else
		ret.b = 255.0 * color.b + 0.5;
	return (TRI_OPAQUE_UNSIGNED | (ret.r << 16) | (ret.g << 8) | ret.b);
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
