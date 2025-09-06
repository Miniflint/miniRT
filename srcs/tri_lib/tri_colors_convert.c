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
