#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
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
int     ft_strlen(char *str);
char    *ft_strjoin(char *s1, char *s2);
char	*readfile(int fd);

/* GET STRUCTS */
t_all	*__get_all(void);

/* INIT */
int    __init__(t_all *all, char **argv);


#endif
