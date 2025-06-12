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

# define BUFF_SIZE 5096

typedef struct S_all
{
	t_amb_light ambient_light;
	t_cam		camera;
	t_light		*lights;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
	char        **argv;
}	t_all;

/* UTILS */
int		        ft_strlen(char *str);
char	        *ft_strjoin(char *s1, char *s2);
char	        *readfile(int fd);
int 	        ft_iswhitespace(char c);
int             ft_nblen(int nb);
int	            ft_strlen(char *str);
unsigned int    ft_atoi(char **s);
double          ft_atof(char **s);
void            skip_till_number(char **s);
int             skip_whitespace_hashtag(char **s);

/* GET STRUCTS */
t_all	*__get_all(void);

/* INIT */
int	__init__(t_all *all, char **argv);
int	__set_values(t_all *all, char **s);

/* PARSING */
int get_rgb(t_rgb *rgb, char **s);
int get_vec(t_vec *vec, char **s);
int get_coord(t_coord *coord, char **s);

int get_ambient_light(t_amb_light *a_light, char **s);
int get_camera(t_cam *camera, char **s);
int get_light(t_light *light, char **s, t_light **head);
int get_sphere(t_sphere *sphere, char **s, t_sphere **head);
int get_plane(t_plane *plane, char **s, t_plane **head);
int get_cylinder(t_cylinder *cylinder, char **s, t_cylinder **head);

#endif
