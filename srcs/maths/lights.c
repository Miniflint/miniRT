#include "miniRT.h"
#include "tri_lib.h"

void	add_color_ray(t_rgb *raycolor, t_rgb *lightcolor, double intensity)
{
	int		color;
	color = (int)(((double)lightcolor->r * intensity) + raycolor->r);
	if (color > 255)
		color = 255;
	raycolor->r = color;
	color = (int)(((double)lightcolor->g * intensity) + raycolor->g);
	if (color > 255)
		color = 255;
	raycolor->g = color;
	color = (int)(((double)lightcolor->b * intensity) + raycolor->b);
	if (color > 255)
		color = 255;
	raycolor->b = color;
}

void	send_light_sphere(t_light *light, t_rgb *raycolor, t_coord p, t_coord c)
{
	t_vec	L;
	t_vec	N;
	double	a_cos;
	double	intensity;
	double	surface_spread;

	sub_vectors(&light->coord, &p, &L);
	sub_vectors(&p, &c, &N);
	norm_vectors(&L, vec_magnitude(&L), &L);
	norm_vectors(&N, vec_magnitude(&N), &N);
	a_cos = 1- dot_product(&N, &L);
	if (a_cos <= 0)
		return ;
	surface_spread = (light->ratio / 2.0) / a_cos;
	intensity = surface_spread / light->ratio;
	add_color_ray(raycolor, &light->rgb, intensity);
}

// void	send_light_sphere(t_light *light, t_rgb *raycolor, t_coord p, t_coord c)
// {
// 	t_vec	L;
// 	t_vec	N;
// 	double	a_cos;
// 	//double	intensity;

// 	sub_vectors(&light->coord, &p, &L);
// 	sub_vectors(&p, &c, &N);
// 	norm_vectors(&L, vec_magnitude(&L), &L);
// 	norm_vectors(&N, vec_magnitude(&N), &N);
// 	a_cos = 1 - dot_product(&N, &L);
// 	if (a_cos <= 0)
// 		return ;
// 	//intensity = light->ratio / a_cos;
// 	//printf("s_s: %f\n", surface_spread);
// 	add_color_ray(raycolor, &light->rgb, a_cos);
// }
