#include "miniRT.h"

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

inline double	dot_product(register t_vec *a, register t_vec *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

#endif
