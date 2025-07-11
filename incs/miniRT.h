#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# if defined(_WIN32) || defined(WIN32)
#  include <windows.h>
# else
#  include <fcntl.h>
#  include <unistd.h>
# endif

# include "miniRT_struct.h"
# include "miniRT_planes.h"
# include "miniRT_objs.h"

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
	char			**argv;
	int				argc;
	unsigned long	line_count;
}	t_all;

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

#endif
