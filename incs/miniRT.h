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

# define BUFF_SIZE 5096

typedef struct S_all
{
	t_amb_light		ambient_light;
	t_cam			camera;
	t_light			*lights;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
	char			**argv;
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
int				skip_whitespace_hashtag(char **s);
void			*ft_memset(void *b, int c, size_t len);

/* NODES */
void			*create_empty_node(size_t size);

/* GET STRUCTS */
t_all			*__get_all(void);

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
int				__init__(t_all *all, char **argv);
int				__set_values(t_all *all, char **s);

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

#endif
