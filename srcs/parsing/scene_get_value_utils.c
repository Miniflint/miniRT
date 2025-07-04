#include "miniRT.h"

int	get_rgb(t_rgb *rgb, char **const restrict s)
{
	const t_minuint	max_rgb_val = 255;
	unsigned int	real_value;

	real_value = ft_atoi(s);
	if (*((*s)++) != ',' ||  !(**s >= '0' && **s <= '9'))
		return (printf(ERROR_R_DECODE, *((*s) - 1), *((*s) - 1), __get_all()->line_count), 1);
	if (real_value > max_rgb_val)
		return (printf("Error: (R)GB value < 0 || > 255\nline [%lu]\n", __get_all()->line_count), 1);
	rgb->r = real_value;
	real_value = ft_atoi(s);
	if (*((*s)++) != ',' ||  !(**s >= '0' && **s <= '9'))
		return (printf(ERROR_G_DECODE, *((*s) - 1), *((*s) - 1), __get_all()->line_count), 1);
	if (real_value > max_rgb_val)
		return (printf("Error: R(G)B value < 0 || > 255\nline [%lu]\n", __get_all()->line_count), 1);
	rgb->g = real_value;
	real_value = ft_atoi(s);
	if (**s && !ft_iswhitespace(**s))
		return (printf(ERROR_B_DECODE, **s, **s, __get_all()->line_count), 1);
	if (real_value > max_rgb_val)
		return (printf("Error: RG(B) value < 0 || > 255\nline [%lu]\n", __get_all()->line_count), 1);
	rgb->b = real_value;
	return (0);
}

int	get_coord(t_coord *coord, char **const restrict s)
{
	coord->x = ft_atof(s);
	if (*((*s)++) != ',' ||  (!(**s >= '0' && **s <= '9') && **s != '-'))
		return (printf(ERROR_X_DECODE, *((*s) - 1), *((*s) - 1), __get_all()->line_count), 1);
	coord->y = ft_atof(s);
	if (*((*s)++) != ',' ||  (!(**s >= '0' && **s <= '9') && **s != '-'))
		return (printf(ERROR_Y_DECODE, *((*s) - 1), *((*s) - 1), __get_all()->line_count), 1);
	coord->z = ft_atof(s);
	if (**s && !ft_iswhitespace(**s))
		return (printf(ERROR_Z_DECODE, **s, **s, __get_all()->line_count), 1);
	return (0);
}

int	get_vec(t_vec *vec, char **const restrict s)
{
	vec->x = ft_atof(s);
	if (*((*s)++) != ',' ||  (!(**s >= '0' && **s <= '9') && **s != '-'))
		return (printf(ERROR_X_DECODE, *((*s) - 1), *((*s) - 1), __get_all()->line_count), 1);
	if (vec->x > 1.0 || vec->x < -1.0)
		return (printf("Error: (X)YZ value < -1.0 || > 1.0\nline [%lu]\n", __get_all()->line_count), 1);
	vec->y = ft_atof(s);
	if (*((*s)++) != ',' ||  (!(**s >= '0' && **s <= '9') && **s != '-'))
		return (printf(ERROR_Y_DECODE, *((*s) - 1), *((*s) - 1), __get_all()->line_count), 1);
	if (vec->y > 1.0 || vec->y < -1.0)
		return (printf("Error: X(Y)Z value < -1.0 || > 1.0\nline [%lu]\n", __get_all()->line_count), 1);
	vec->z = ft_atof(s);
	if (**s && !ft_iswhitespace(**s))
		return (printf(ERROR_Z_DECODE, **s, **s, __get_all()->line_count), 1);
	if (vec->z > 1.0 || vec->z < -1.0)
		return (printf("Error: XY(Z) value < -1.0 || > 1.0\nline [%lu]\n", __get_all()->line_count), 1);
	return (0);
}
