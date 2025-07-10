#include "miniRT.h"

double vec_magnitude(t_coord *a)
{
	return (sqrt((a->x * a->x) + (a->y * a->y) + (a->z * a->z)));
}

void	add_vectors(t_coord *a, t_coord *b, t_coord *c)
{
	c->x = a->x + b->x;
	c->y = a->y + b->y;
	c->z = a->z + b->z;
}

void	sub_vectors(t_coord *a, t_coord *b, t_coord *c)
{
	c->x = a->x - b->x;
	c->y = a->y - b->y;
	c->z = a->z - b->z;
}

void	mul_vectors(t_coord *a, t_coord *b, t_coord *c)
{
	c->x = a->x * b->x;
	c->y = a->y * b->y;
	c->z = a->z * b->z;
}

void	div_vectors(t_coord *a, t_coord *b, t_coord *c)
{
	c->x = a->x / b->x;
	c->y = a->y / b->y;
	c->z = a->z / b->z;
}

void	scalar_product(t_coord *a, double b, t_coord *c)
{
	c->x = a->x * b;
	c->y = a->y * b;
	c->z = a->z * b;
}

void norm_vectors(t_coord *a, double magnitude, t_coord *c)
{
	c->x = a->x / magnitude;
	c->y = a->y / magnitude;
	c->z = a->z / magnitude;
}

double dot_product(t_coord *a, t_coord *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

double get_angle(t_coord *a, t_coord *b, double mag_a, double mag_b)
{
	return (acos(dot_product(a, b) / (mag_a * mag_b)));
}

double cross_product(t_coord *a, t_coord *b, t_coord *c)
{
	c->x = (a->y * b->z) - (a->z * b->y);
	c->y = (a->z * b->x) - (a->x * b->z);
	c->z = (a->x * b->y) - (a->y * b->x);
}
