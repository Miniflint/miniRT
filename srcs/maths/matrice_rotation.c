#include "miniRT.h"

// void rotate_camera_x(t_vec *dir_rotate, double nb)
// {
// 	const double pre_compute_sin = sin(nb);
// 	const double pre_compute_cos = cos(nb);

// 	t_vec const	dir = {
// 		.x = dir_rotate->x,
// 		.y = dir_rotate->y * pre_compute_cos
		// - (dir_rotate->z * pre_compute_sin),
// 		.z = dir_rotate->y * pre_compute_sin
		// + (dir_rotate->z * pre_compute_cos),
// 	};
// 	*dir_rotate = dir;
// }

// void rotate_camera_y(t_vec *dir_rotate, double nb)
// {
// 	const double pre_compute_sin = sin(nb);
// 	const double pre_compute_cos = cos(nb);

// 	t_vec const	dir = {
// 		.x = dir_rotate->x * pre_compute_cos + dir_rotate->z * pre_compute_sin,
// 		.y = dir_rotate->y,
// 		.z = -dir_rotate->x * pre_compute_sin + dir_rotate->z * pre_compute_cos,
// 	};
// 	*dir_rotate = dir;
// }

// void rotate_camera_z(t_vec *dir_rotate, double nb)
// {
// 	const double pre_compute_sin = sin(nb);
// 	const double pre_compute_cos = cos(nb);

// 	t_vec const	dir = {
// 		.x = dir_rotate->x * pre_compute_cos - dir_rotate->y * pre_compute_sin,
// 		.y = dir_rotate->x * pre_compute_sin + dir_rotate->y * pre_compute_cos,
// 		.z = dir_rotate->z,
// 	};
// 	*dir_rotate = dir;
// }

//v' = v * cosθ + (k × v) * sinθ + k * (k · v) * (1 - cosθ)
//v' = v * cosθ + (k × v) * sinθ

// int	rotate_camera(t_vec *original, t_vec *axis,
	// t_vec *for_perpendicular, double angle)
// {
// 	t_vec	rotated;
// 	t_vec	tmp;
// 	double	mag;

// 	// add_vectors(scalar_multiplication_no_v(original, cos(angle)),
// 		// mul_vectors(cross_product(axis, original, &perp),
// 		// axis, &tmp), original)
// 	// v' = v * cosθ + (k x v) * sinθ
// 	// v' = rotated + (k x v) * sinθ
// 	// v' = rotated + perpendiculat * sinθ
// 	// v' = rotated + tmp
// 	// v' = original_rotated
// 	// for_perp = cross(k x v)
// 	// original = original * cos(angle) +
// //	(cross_product(around, original, &rotated)) * sin(angle);

// 	add_vectors(scalar_multiplication(original, cos(angle), &rotated),
// 		scalar_multiplication(for_perpendicular, sin(angle), &tmp), original);
// 	//add_vectors(scalar_multiplication(original, cos(angle), &rotated),
// 	//	scalar_multiplication(cross_product(axis, original, for_perpendicular),
// 		// sin(angle), &tmp), original);

// 	cross_product(original, axis, &tmp);
// 	mag = dot_product(&tmp, for_perpendicular);
// 	if (mag < 0)
// 		scalar_multiplication(&tmp, -1, for_perpendicular);
// 	else
// 		*for_perpendicular = tmp;
// 	mag = vec_magnitude(original);
// 	norm_vectors(original, mag, original);
// 	mag = vec_magnitude(axis);
// 	norm_vectors(axis, mag, axis);
// 	mag = vec_magnitude(for_perpendicular);
// 	norm_vectors(for_perpendicular, mag, for_perpendicular);
// 	return (3);
// }

int	rotate_camera(t_vec *original, t_vec *axis,
		t_vec *for_perpendicular, double angle)
{
	t_vec	rotated;
	t_vec	tmp;
	double	mag;

	add_vectors(scalar_multiplication(original, cos(angle), &rotated),
		scalar_multiplication(for_perpendicular, sin(angle), &tmp), original);
	cross_product(original, axis, &tmp);
	mag = dot_product(&tmp, for_perpendicular);
	if (mag < 0)
		scalar_multiplication(&tmp, -1, for_perpendicular);
	else
		*for_perpendicular = tmp;
	mag = vec_magnitude(original);
	norm_vectors(original, mag, original);
	mag = vec_magnitude(axis);
	norm_vectors(axis, mag, axis);
	mag = vec_magnitude(for_perpendicular);
	norm_vectors(for_perpendicular, mag, for_perpendicular);
	return (3);
}
