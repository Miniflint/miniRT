#include "miniRT.h"

void rotate_camera_x(t_vec *dir_rotate, double nb)
{
	t_vec const	dir = {
		.x = dir_rotate->x,
		.y = dir_rotate->y * cos(nb) - (dir_rotate->z * sin(nb)),
		.z = dir_rotate->y * sin(nb) + (dir_rotate->z * cos(nb)),
	};
	*dir_rotate = dir;
}

void rotate_camera_y(t_vec *dir_rotate, double nb)
{
	t_vec const	dir = {
		.x = dir_rotate->x * cos(nb) + dir_rotate->z * sin(nb),
		.y = dir_rotate->y,
		.z = -dir_rotate->x * sin(nb) + dir_rotate->z * cos(nb),
	};
	*dir_rotate = dir;
}

void rotate_camera_z(t_vec *dir_rotate, double nb)
{
	t_vec const	dir = {
		.x = dir_rotate->x * cos(nb) - dir_rotate->y * sin(nb),
		.y = dir_rotate->x * sin(nb) + dir_rotate->y * cos(nb),
		.z = dir_rotate->z,
	};
	*dir_rotate = dir;
}