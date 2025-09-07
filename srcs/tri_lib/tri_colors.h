/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_colors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 02:44:16 by hermesrolle       #+#    #+#             */
/*   Updated: 2025/09/07 02:44:17 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRI_COLORS_H
# define TRI_COLORS_H
# ifdef __linux__
#  define TRI_OPAQUE_UNSIGNED 0xFF000000
#  define TRI_TRANSPARENT_UNSIGNED 0x00000000
#  define TRI_OPAQUE 1
#  define TRI_TRANSPARENT 0
# else
#  define TRI_OPAQUE_UNSIGNED 0x00000000
#  define TRI_TRANSPARENT_UNSIGNED 0xFF000000
#  define TRI_OPAQUE 0
#  define TRI_TRANSPARENT 1
# endif

typedef unsigned char	t_color;

typedef struct s_argb
{
	double	a;
	t_color	r;
	t_color	g;
	t_color	b;
}			t_argb;

typedef struct s_rgb_f
{
	double	r;
	double	g;
	double	b;
}			t_rgb_f;

t_argb			unsigned_to_argb(unsigned int color);
unsigned int	argb_to_unsigned(t_argb color);
unsigned int	rgb_f_to_unsigned(t_rgb_f color);
t_rgb_f			argb_to_rgbf(t_argb color);
t_argb			rgb_f_to_argb(t_rgb_f color);
t_argb			mix_colors_normal(t_argb top, t_argb base);
unsigned int	mix_colors_normal_u_no_a(t_argb top, t_argb base);
unsigned int	_mix_colors_render_to_render(t_argb top, t_argb base);
unsigned int	mix_colors_normal_u(t_argb top, t_argb base);
t_rgb_f			clamp_rgb_f(t_rgb_f color);

#endif