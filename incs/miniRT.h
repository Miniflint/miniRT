#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <sys/time.h>
# if defined(_WIN32) || defined(WIN32)
#  include <windows.h>
# else
#  include <fcntl.h>
#  include <unistd.h>
# endif
# ifndef WIN_WIDTH_ALL
#  define WIN_WIDTH_ALL 1080
# endif
# ifndef WIN_HEIGHT_ALL
#  define WIN_HEIGHT_ALL 720
# endif
# ifndef DISTANCE_LIGHT_MIDDLE
#  define DISTANCE_LIGHT_MIDDLE 200
# endif
# define MOVE_CAM_SPEED 3
# define ROT_CAM_SPEED 0.035
# include "tri_lib.h"
# include "miniRT_struct.h"
# include "miniRT_planes.h"
# include "miniRT_objs.h"
# define PI_DEFINED 3.14159265358979323846

# define BUFF_SIZE 32768
//# define BUFF_SIZE 1

typedef struct S_all
{
	t_amb_light		ambient_light;
	t_cam			camera;
	t_light			*lights;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
	t_object		*objects;
	t_canvas		canvas;
	char			**argv;
	int				argc;
	int				win_height;
	int				win_width;
	char			shadow_on;
	unsigned long	line_count;
	double			light_ratio;
	double			distance_light;
}	t_all;

typedef struct S_shape_closest
{
	double	t;
	t_vec	normal;
	t_rgb	color;
	void	*shape;
	int		type;

	t_sphere	*sp_closest;
	t_plane		*pl_closest;
	t_cylinder	*cy_closest;
	t_object	*ob_closest;
	t_rgb		colors;
	double		sp_t1;
	double		sp_t2;
	double		pl_t1;
}	t_shape_closest;

/* UTILS */
int				ft_strlen(char *str);
char			*ft_strjoin(char *s1, char *s2);
char			*readfile(int fd);
int				ft_iswhitespace(char c);
int				ft_nblen(int nb);
int				ft_strlen(char *str);
unsigned int	ft_atoi(char **s);
double			ft_atof(char **s);
int				skip_till_number(char **s, int nb);
int				skip_whitespace_hashtag(char **s, unsigned long *line_count);
void			*ft_memset(void *b, int c, size_t len);
int				ft_strncmp(char *s1, const char *s2, size_t n);

/* NODES */
void			*create_empty_node(size_t size);

/* GET STRUCTS */
t_all			*__get_all(void);
t_object		*__get_head(t_object *curr_head);

/* FREE */
t_light			*free_l(t_light *light);
t_sphere		*free_sp(t_sphere *sphere);
t_plane			*free_pl(t_plane *plane);
t_cylinder		*free_cy(t_cylinder *cylinder);
t_object		*free_objs(t_object *obj);
// void			free_all(t_all *all);
int				free_all(void *content);

/* PRINTING */
void			print_all_structs(t_all *all);
void			print_ac(t_amb_light *ambient_light, t_cam *camera);
void			print_l(t_light *light, int depth);
void			print_sp(t_sphere *sphere, int depth);
void			print_pl(t_plane *plane, int depth);
void			print_cy(t_cylinder *cylinder, int depth);
void			print_ob(t_object *object, int depth);

/* INIT */
int				__init__(t_all *all, char **argv, int argc);
int				__set_values_scene(t_all *all, char **s);
int				__set_values_objs(t_object *object, char **s);

/* MATHS */
int ft_mult(int x, int y);

/* PARSING */
int				get_rgb(t_rgb *rgb, char **const restrict s);
int				get_vec(t_vec *vec, char **const restrict s);
int				get_coord(t_coord *coord, char **const restrict s);

int				get_ambient_light(t_amb_light *a_light, char **const restrict s);
int				get_camera(t_cam *camera, char **const restrict s);
int				get_light(t_light **head, char **const restrict s);
int				get_sphere(t_sphere **head, char **const restrict s);
int				get_plane(t_plane **head, char **const restrict s);
int				get_cylinder(t_cylinder **head, char **const restrict s);
int				parse_type_scene(t_all *all, char **s);
int				parse_type_objs(t_object *object, char **s);
int 			get_name(char name[128], char **const restrict s);
int				get_letters(t_object *object, const char *restrict s);
int				__mallocate_objs_values(t_object *object, char *str);

int				get_vertices(t_vertice *vertice, char **const restrict s, int skip, unsigned long *index);
int				get_faces(t_face *face, char **const restrict s,
					t_minuint curr_smoothing, unsigned long *index);
int				get_smoothing(t_minuint *curr_smoothing, char **const restrict s);
t_object		*create_obj_path(t_object **head, char *path);
void 			zeroes_two(t_object *object, char *path);
int				get_obj(t_object **head, char **const restrict s);


/* UTILS MATHS */
void 	start_rays(t_all *all);
double	vec_magnitude(t_vec *a);
t_vec	*add_vectors(t_vec *a, t_vec *b, t_vec *c);
t_vec	*sub_vectors(t_vec *a, t_vec *b, t_vec *c);
t_vec	sub_vectors_no_v(t_vec *a, t_vec *b);
t_vec	*div_vectors(t_vec *a, t_vec *b, t_vec *c);
t_vec	*scalar_multiplication(t_vec *a, double b, t_vec *c);
t_vec	scalar_multiplication_no_v(t_vec *a, double b);
t_vec	*norm_vectors(t_vec *a, double magnitude, t_vec *c);
double	dot_product(register t_vec *a, register t_vec *b);
double	get_angle(t_vec *a, t_vec *b, double mag_a, double mag_b);
t_vec	*cross_product(t_vec *a, t_vec *b, t_vec *c);
// char	get_fps_tick(unsigned int fps, unsigned long *ret, int reset);

unsigned int	traceray(t_ray *ray, t_all *all);
void			oldIntersectRaySphere(double a, t_vec *D, t_vec *O, t_sphere *sphere,
					double *t1, double *t2);
void			IntersectRaySphere(t_ray *ray, t_sphere *sphere);
void			intersect_plane(t_ray *ray, t_plane *plane);
void			make_perpendicular(t_cam *cam);
void			cal_fov(t_all *all);
void			cal_rays(t_all *all);
void			init_start_ray(t_all *all);
void			reset_rays(t_all *all);
// void			update_rays_start(t_all *all);
// void			send_light_sphere(t_light *light, t_rgb *raycolor, t_coord p, t_sphere *sphere);

void rotate_camera_x(t_vec *dir_rotate, double nb);
void rotate_camera_y(t_vec *dir_rotate, double nb);
void rotate_camera_z(t_vec *dir_rotate, double nb);

int	rotate_camera(t_vec *original, t_vec *axis, t_vec *for_perpendicular, double angle);

void	diffuse_light(t_ray *ray, t_all *all, t_light *light);

#endif
