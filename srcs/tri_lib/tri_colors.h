#ifndef TRI_COLORS_H
# define TRI_COLORS_H

typedef unsigned char	t_color;

typedef struct s_argb
{
	double	a;
	t_color	r;
	t_color	g;
	t_color	b;
}			t_argb;

t_argb			unsigned_to_argb(unsigned int color);
unsigned int	argb_to_unsigned(t_argb color);
t_argb			mix_colors_normal(t_argb top, t_argb base);
unsigned int	mix_colors_normal_u_no_a(t_argb top, t_argb base);
unsigned int	_mix_colors_render_to_render(t_argb top, t_argb base);
unsigned int	mix_colors_normal_u(t_argb top, t_argb base);

#endif