#include "miniRT.h"

void rotate_camera_x(t_vec *dir_rotate, double nb)
{
	const double pre_compute_sin = sin(nb);
	const double pre_compute_cos = cos(nb);

	t_vec const	dir = {
		.x = dir_rotate->x,
		.y = dir_rotate->y * pre_compute_cos - (dir_rotate->z * pre_compute_sin),
		.z = dir_rotate->y * pre_compute_sin + (dir_rotate->z * pre_compute_cos),
	};
	*dir_rotate = dir;
}

void rotate_camera_y(t_vec *dir_rotate, double nb)
{
	const double pre_compute_sin = sin(nb);
	const double pre_compute_cos = cos(nb);

	t_vec const	dir = {
		.x = dir_rotate->x * pre_compute_cos + dir_rotate->z * pre_compute_sin,
		.y = dir_rotate->y,
		.z = -dir_rotate->x * pre_compute_sin + dir_rotate->z * pre_compute_cos,
	};
	*dir_rotate = dir;
}

void rotate_camera_z(t_vec *dir_rotate, double nb)
{
	const double pre_compute_sin = sin(nb);
	const double pre_compute_cos = cos(nb);

	t_vec const	dir = {
		.x = dir_rotate->x * pre_compute_cos - dir_rotate->y * pre_compute_sin,
		.y = dir_rotate->x * pre_compute_sin + dir_rotate->y * pre_compute_cos,
		.z = dir_rotate->z,
	};
	*dir_rotate = dir;
}
