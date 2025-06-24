#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>
# ifdef __unix__
#  include <fcntl.h>
#  include <unistd.h>
# elif defined(_WIN32) || defined(WIN32)
#  include <windows.h>
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
	t_object		*head_obj;
	char			**argv;
	int				argc;
	unsigned int	line_count;
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
int				skip_whitespace_hashtag(char **s, unsigned int *line_count);
int				skip_whitespace_hashtag_u(char **s, unsigned long *line_count);
void			*ft_memset(void *b, int c, size_t len);
int				ft_strncmp(char *s1, const char *s2, size_t n);

/* NODES */
void			*create_empty_node(size_t size);

/* GET STRUCTS */
t_all			*__get_all(void);
t_object		*__get_head(t_object *curr_head);

/* FREE */
void			free_l(t_light *light);
void			free_sp(t_sphere *sphere);
void			free_pl(t_plane *plane);
void			free_cy(t_cylinder *cylinder);
void			free_all(t_all *all);

/* PRINTING */
void			print_all_structs(t_all *all);
void			print_ac(t_amb_light *ambient_light, t_cam *camera);
void			print_l(t_light *light, int depth);
void			print_sp(t_sphere *sphere, int depth);
void			print_pl(t_plane *plane, int depth);
void			print_cy(t_cylinder *cylinder, int depth);

/* INIT */
int				__init__(t_all *all, char **argv, int argc);
int				__set_values_scene(t_all *all, char **s);
int				__set_values_objs(t_object *object, char **s);

/* PARSING */
int				get_rgb(t_rgb *rgb, char **s);
int				get_vec(t_vec *vec, char **s);
int				get_coord(t_coord *coord, char **s);

int				get_ambient_light(t_amb_light *a_light, char **s);
int				get_camera(t_cam *camera, char **s);
int				get_light(t_light **head, char **s);
int				get_sphere(t_sphere **head, char **s);
int				get_plane(t_plane **head, char **s);
int				get_cylinder(t_cylinder **head, char **s);
int				parse_type_scene(t_all *all, char **s);
int				parse_type_objs(t_object *object, char **s);
int 			get_name(char name[128], char **s);
int				get_letters(t_object *object, const char *restrict s);
int				__mallocate_objs_values(t_object *object, char *str);

#endif
