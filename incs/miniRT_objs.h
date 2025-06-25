#ifndef MINIRT_OBJS_H
# define MINIRT_OBJS_H

# include "miniRT.h"

# define I_VERTEX 0
# define I_FACES 1
# define I_POINTS 2

typedef struct	S_vertice
{
	double	x;
	double	y;
	double	z;
}				t_vertice;

typedef t_vertice t_vertice_texture;
typedef t_vertice t_vertice_normale;

typedef struct S_point
{
	char				is_wrong;
	unsigned long		v_indexes;
	t_vertice			*vertices;
	struct S_point	*next;
}	t_point;

/* 
 * p_x = POINT_NUMBER_X (1,2,3)
 * t_x = TEXTURE_NUMBER_X (1,2,3)
 * n_x = NORMALE_NUMBER_X (1,2,3)
 * 
 * point: index associated vertice (v) (x y x). 
 * texture: index associated with the vt (vt). it has 
 */


 // TODO. POINTER ON VERTEXES, VERTEXES TEXTURES, VERTEX NORMALES
typedef struct S_face
{
	char				is_wrong;
	unsigned long		v_indexes[4];
	t_vertice			*vertices[4];
	t_minuint	smoothing;
}				t_face;

typedef struct S_object
{
	char			name[128];
	char			*path;
	t_vertice		*vertices;
	t_face			*faces;
	t_point			*points;
	t_minuint		curr_smoothing;
	unsigned long	indexes[3];
	unsigned long	line_count;
	unsigned long	nb_vertices;
	unsigned long	nb_faces;
	unsigned long	nb_points;
	struct S_object	*next;

}	t_object;

#endif