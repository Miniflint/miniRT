#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

# include "miniRT.h"
# include "tri_colors.h"
# include <pthread.h>

# define ERROR_X_DECODE "Error (X)YZ coordinates @: [%d|%c]\nline [%lu]\n"
# define ERROR_Y_DECODE "Error X(Y)Z coordinates @: [%d|%c]\nline [%lu]\n"
# define ERROR_Z_DECODE "Error XY(Z) coordinates @: [%d|%c]\nline [%lu]\n"

# define VEC_ERROR_X_DECODE "Error: (X)YZ value < -1.0 || > 1.0\nline [%lu]\n"
# define VEC_ERROR_Y_DECODE "Error: X(Y)Z value < -1.0 || > 1.0\nline [%lu]\n"
# define VEC_ERROR_Z_DECODE "Error: XY(Z) value < -1.0 || > 1.0\nline [%lu]\n"

# define ERROR_R_DECODE "Error (R)GB color @: [%d|%c]\nline [%lu]\n"
# define ERROR_G_DECODE "Error R(G)B color @: [%d|%c]\nline [%lu]\n"
# define ERROR_B_DECODE "Error RG(B) color @: [%d|%c]\nline [%lu]\n"

// struct timeval	{
// 	time_t		tv_sec;
// 	susecond_t	tv_usec;
// };
typedef struct S_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef struct s_quad
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;
}			t_quad;

// typedef struct S_rgb_norm
// {
// 	double	r;
// 	double	g;
// 	double	b;
// }	t_rgb_norm;

typedef unsigned char	t_minuint;
typedef struct S_all	t_all;
typedef t_coord			t_vec;
typedef t_argb			t_rgb;

// typedef struct S_rgb
// {
// 	t_minuint	r;
// 	t_minuint	g;
// 	t_minuint	b;
// }	t_rgb;

typedef struct s_light_vec
{
	t_vec	light_dir;
	double	light_lenght;
}			t_light_vec;

typedef enum e_thread_mode
{
	CONTINUE,
	PAUSE,
	STOP,
	RESET,
	NONE
}	t_thread_mode;

typedef struct s_threads
{
	t_thread_mode	mode;
	pthread_t		thread;
	int				start;
	int				end;
	struct timeval	start_time;
	unsigned long	average_time;
	t_all			*all;
}					t_threads;

typedef enum E_obj_type
{
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	BOX,
	OBJECT,
	TRIANGLE,
	HITBOX,
	END_SHAPE
}	t_obj_type;

typedef enum E_node_type
{
	ROOT,
	INTERNAL,
	LEAF
}	t_node_type;

typedef struct s_shape
{
	t_obj_type	type;
	double		t1;
	double		t2;
	t_vec		normal;
	t_coord		origin;
	void		*shape;
}				t_shape;

typedef struct S_ray
{
	t_coord	start;
	t_coord	hit;
	t_vec	dir;
	t_rgb_f	color;
	t_rgb_f	color_ray;
	t_rgb_f	color_shape;
	t_rgb_f	color_diffuse;
	t_shape	shape;
	int		x;
	int		y;
}	t_ray;

typedef struct S_Canvas
{
	double			size_x;
	double			size_y;
	double			unit;
	t_minuint		pixel_values;
	double			pix_x[WIN_WIDTH_ALL];
	double			pix_y[WIN_HEIGHT_ALL];
	t_ray			rays[WIN_HEIGHT_ALL][WIN_WIDTH_ALL];
	t_ray			rays_save[WIN_HEIGHT_ALL][WIN_WIDTH_ALL];
}	t_canvas;	

typedef struct S_bvh
{
	t_vec	top[4];
	t_vec	bottom[4];
	t_vec	*a;
	t_vec	*b;
}	t_bvh;

typedef struct S_box
{
	t_bvh			box;
	t_rgb			rgb;
	t_rgb			rgb_save;
	t_rgb_f			color;
	struct S_box	*next;
}	t_box;


typedef struct S_hitbox
{
	t_bvh			box;
	void			*shape;
	t_obj_type		type;
	t_node_type		node_type;
	int				depth;
	struct S_hitbox	*left;
	struct S_hitbox	*right;
}	t_hitbox;

typedef struct S_task{
	int start;
	int end;
	int depth;
	t_hitbox **out;  // Pointer where the built node should be stored
} t_task;

#endif