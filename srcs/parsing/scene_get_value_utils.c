/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_get_value_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:06:04 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:06:16 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_rgb(t_rgb *rgb, char **const restrict s)
{
	const t_minuint		max_rgb_val = 255;
	unsigned int		real_value;
	const unsigned long	lc = __get_all()->line_count;

	real_value = ft_atoi(s);
	if (*((*s)++) != ',' || !(**s >= '0' && **s <= '9'))
		return (printf(ERROR_R_DECODE, *((*s - (*(*s - 1) == ' '))),
				*((*s - (*(*s - 1) == ' '))), lc), 1);
	if (real_value > max_rgb_val)
		return (printf("Error: (R)GB value < 0 || > 255\nline [%lu]\n", lc), 1);
	rgb->r = real_value;
	real_value = ft_atoi(s);
	if (*((*s)++) != ',' || !(**s >= '0' && **s <= '9'))
		return (printf(ERROR_G_DECODE, *((*s - (*(*s - 1) == ' '))),
				*((*s - (*(*s - 1) == ' '))), lc), 1);
	if (real_value > max_rgb_val)
		return (printf("Error: R(G)B value < 0 || > 255\nline [%lu]\n", lc), 1);
	rgb->g = real_value;
	real_value = ft_atoi(s);
	if (**s && !ft_iswhitespace(**s))
		return (printf(ERROR_B_DECODE, **s, **s, lc), 1);
	if (real_value > max_rgb_val)
		return (printf("Error: RG(B) value < 0 || > 255\nline [%lu]\n", lc), 1);
	rgb->b = real_value;
	return (0);
}

int	get_coord(t_coord *coord, char **const restrict s)
{
	const unsigned long	lc = __get_all()->line_count;

	coord->x = ft_atof(s);
	if (*((*s)++) != ',' || (!(**s >= '0' && **s <= '9') && **s != '-'))
		return (printf(ERROR_X_DECODE, *((*s - (*(*s - 1) == ' '))),
				*((*s - (*(*s - 1) == ' '))), lc), 1);
	coord->y = ft_atof(s);
	if (*((*s)++) != ',' || (!(**s >= '0' && **s <= '9') && **s != '-'))
		return (printf(ERROR_Y_DECODE, *((*s - (*(*s - 1) == ' '))),
				*((*s - (*(*s - 1) == ' '))), lc), 1);
	coord->z = ft_atof(s);
	if (**s && !ft_iswhitespace(**s))
		return (printf(ERROR_Z_DECODE, **s, **s, lc), 1);
	return (0);
}

int	get_vec(t_vec *vec, char **const restrict s)
{
	const unsigned long	lc = __get_all()->line_count;

	vec->x = ft_atof(s);
	if (*((*s)++) != ',' || (!(**s >= '0' && **s <= '9') && **s != '-'))
		return (printf(ERROR_X_DECODE, *((*s - (*(*s - 1) == ' '))),
				*((*s - (*(*s - 1) == ' '))), lc), 1);
	if (vec->x > 1.0 || vec->x < -1.0)
		return (printf(VEC_ERROR_X_DECODE, lc), 1);
	vec->y = ft_atof(s);
	if (*((*s)++) != ',' || (!(**s >= '0' && **s <= '9') && **s != '-'))
		return (printf(ERROR_Y_DECODE, *((*s - (*(*s - 1) == ' '))),
				*((*s - (*(*s - 1) == ' '))), lc), 1);
	if (vec->y > 1.0 || vec->y < -1.0)
		return (printf(VEC_ERROR_Y_DECODE, lc), 1);
	vec->z = ft_atof(s);
	if (**s && !ft_iswhitespace(**s))
		return (printf(ERROR_Z_DECODE, **s, **s, lc), 1);
	if (vec->z > 1.0 || vec->z < -1.0)
		return (printf(VEC_ERROR_Z_DECODE, lc), 1);
	if (vec->x == 0 && vec->y == 0 && vec->z == 0)
		return (printf("Error: vec(XYZ) can't be only 0\nline [%lu]\n", lc), 1);
	norm_vectors(vec, vec_magnitude(vec), vec);
	return (0);
}
