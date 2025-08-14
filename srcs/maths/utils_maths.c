#include "miniRT.h"

double vec_magnitude(t_vec *a)
{
	return (sqrt((a->x * a->x) + (a->y * a->y) + (a->z * a->z)));
}

t_vec	*add_vectors(t_vec *a, t_vec *b, t_vec *c)
{
	c->x = a->x + b->x;
	c->y = a->y + b->y;
	c->z = a->z + b->z;
	return (c);
}

t_vec	*sub_vectors(t_vec *a, t_vec *b, t_vec *c)
{
	c->x = a->x - b->x;
	c->y = a->y - b->y;
	c->z = a->z - b->z;
	return (c);
}

t_vec	*mul_vectors(t_vec *a, t_vec *b, t_vec *c)
{
	c->x = a->x * b->x;
	c->y = a->y * b->y;
	c->z = a->z * b->z;
	return (c);
}

t_vec	*div_vectors(t_vec *a, t_vec *b, t_vec *c)
{
	c->x = a->x / b->x;
	c->y = a->y / b->y;
	c->z = a->z / b->z;
	return (c);
}

t_vec	*scalar_multiplication(t_vec *a, double b, t_vec *c)
{
	c->x = a->x * b;
	c->y = a->y * b;
	c->z = a->z * b;
	return (c);
}

t_vec	scalar_multiplication_no_v(t_vec *a, double b)
{
	t_vec	c;

	c.x = a->x * b;
	c.y = a->y * b;
	c.z = a->z * b;
	return (c);
}

t_vec	*norm_vectors(t_vec *a, double magnitude, t_vec *c)
{
	c->x = a->x / magnitude;
	c->y = a->y / magnitude;
	c->z = a->z / magnitude;
	return (c);
}

#ifdef __linux__

inline double	dot_product(register t_vec *a, register t_vec *b)
{
	double	result;

	__asm__ (
		"movsd (%%rdi), %%xmm0;"
		"movsd 8(%%rdi), %%xmm1;"
		"mulsd (%%rsi), %%xmm0;"
		"mulsd 8(%%rsi), %%xmm1;"
		"addsd %%xmm1, %%xmm0;"
		"movsd 16(%%rdi), %%xmm1;"
		"mulsd 16(%%rsi), %%xmm1;"
		"addsd %%xmm1, %%xmm0;"
		"movsd %%xmm0, %0;"
		: "=m" (result)
		: "r" (a), "r" (b)
		: "%xmm0", "%xmm1");
	return (result);
}

#else

inline double	dot_product(register t_vec *a, register t_vec *b);
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

#endif

double get_angle(t_vec *a, t_vec *b, double mag_a, double mag_b)
{
	return (acos(dot_product(a, b) / (mag_a * mag_b)));
}

t_vec	*cross_product(t_vec *a, t_vec *b, t_vec *c)
{
	c->x = (a->y * b->z) - (a->z * b->y);
	c->y = (a->z * b->x) - (a->x * b->z);
	c->z = (a->x * b->y) - (a->y * b->x);
	return (c);
}
