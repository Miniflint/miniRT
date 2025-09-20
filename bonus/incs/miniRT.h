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
#  define WIN_WIDTH_ALL 1920
# endif
# ifndef WIN_HEIGHT_ALL
#  define WIN_HEIGHT_ALL 1080
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
# include <pthread.h>
# define PI_DEFINED 3.14159265358979323846
// # define THREADS

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
	t_box			*boxes;
	t_object		*objects;
	t_canvas		canvas;
	t_shape			*shapes;
	t_hitbox		*bvh;
	t_render		*render_hb;
	int				render_hitbox;
	int				nb_shapes;
	int				nb_items;
	char			**argv;
	int				argc;
	int				win_height;
	int				win_width;
	char			shadow_on;
	char			render_on;
	unsigned long	line_count;
	double			light_ratio;
	double			distance_light;
	t_threads		*threads;
	long			n_thread;
	pthread_mutex_t	mutex;
	t_thread_mode	thread_mode;
	unsigned int	thread_states[4];
}					t_all;

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
void			print_bx(t_box *box, int depth);			
void			print_ob(t_object *object, int depth);
void			print_vec(t_vec v);

/* INIT */
int				__init__(t_all *all, char **argv, int argc);
int				__set_values_scene(t_all *all, char **s);
int				__set_values_objs(t_object *object, char **s);
void			__init_faces(t_face *face, unsigned char vert_ind[3],
					int *err, int *i);
int				check_ext(char **argv);
void			apply_argb_save_rgb(t_rgb *rgb_save,
					t_rgb_f ambient_rgb, t_rgb *into);
void			apply_rgb_all_shape(t_all *all);
void			_init_canvas(t_all *all);
unsigned long 	get_depth_objs(t_object *root);
void 			sort_shape(t_shape *arr);

/* PARSING */
int				get_rgb(t_rgb *rgb, char **const restrict s);
int				get_vec(t_vec *vec, char **const restrict s);
int				get_coord(t_coord *coord, char **const restrict s);
int				get_ambient_light(t_amb_light *a_light,
					char **const restrict s);
int				get_material(t_material *material, char **const restrict s);
int				get_camera(t_cam *camera, char **const restrict s);
int				get_light(t_light **head, char **const restrict s);
int				get_sphere(t_sphere **head, char **const restrict s);
int				get_plane(t_plane **head, char **const restrict s);
int				get_cylinder(t_cylinder **head, char **const restrict s);
int				get_box(t_box **head, char **const restrict s);
int				parse_type_scene(t_all *all, char **s);
int				parse_type_objs(t_object *object, char **s);
int				__parse_file_objs(t_all *all);
int				get_name(char name[128], char **const restrict s);
int				get_letters(t_object *object, const char *restrict s);
int				__mallocate_objs_values(t_object *object, char *str);

int				get_vertices(t_vertice *vertice, char **const restrict s,
					int skip, unsigned long *index);
int				get_faces(t_face *face, char **const restrict s,
					t_minuint curr_smoothing, unsigned long *index);
int				get_smoothing(t_minuint *curr_smoothing,
					char **const restrict s);
t_object		*create_obj_path(t_object **head, char *path);
void			zeroes_two(t_object *object, char *path);
int				get_obj(t_object **head, char **const restrict s);
int				set_tmp(unsigned long *tmp, unsigned char slashes,
					char **const restrict s);
int				set_face_parts(t_face *face, char **const restrict s,
					unsigned char vert_ind[3]);
int				get_each_part_face(t_face *face, char **const restrict s,
					unsigned char ind[3]);
int				count_duplicates(void *arr[4]);

/* UTILS MATHS */

void			start_rays(t_all *all);
double			vec_magnitude(t_vec *a);
t_vec			*add_vectors(t_vec *a, t_vec *b, t_vec *c);
t_vec			*sub_vectors(t_vec *a, t_vec *b, t_vec *c);
t_vec			sub_vectors_no_v(t_vec *a, t_vec *b);
t_vec			*scalar_multiplication(t_vec *a, double b, t_vec *c);
t_vec			scalar_multiplication_no_v(t_vec *a, double b);
t_vec			*norm_vectors(t_vec *a, double magnitude, t_vec *c);
double			dot_product(register t_vec *a, register t_vec *b);
t_vec			*cross_product(t_vec *a, t_vec *b, t_vec *c);
double			distance_formula(t_vec *a, t_vec *b);

// unsigned int	traceray(t_ray *ray, t_all *all);
void			traceray(t_ray *ray, t_all *all);
void			intersect_ray_sphere(t_ray *ray, t_sphere *sphere);
void			intersect_plane(t_ray *ray, t_plane *plane);
void			make_perpendicular(t_cam *cam);
void			cal_fov(t_all *all);
void			cal_rays(t_all *all);
void			init_start_ray(t_all *all);
void			reset_rays(t_all *all);
int				rotate_camera(t_vec *original, t_vec *axis,
					t_vec *for_perpendicular, double angle);
void			diffuse_light(t_ray *ray, t_all *all, t_light *light);
void			get_local_color(t_ray *ray, t_all *all);
void			init_color_ray(t_ray *ray);
void			traceray_reflection(t_ray *ray, t_all *all);
void			closest_cylinder(t_ray *ray, t_cylinder *cylinder);
void			closest_box(t_ray *ray, t_box *boxes);

int				sphere_on_the_path(t_ray *ray, t_sphere *sphere,
					t_vec light_dir, double light_length);
int				plane_on_the_path(t_ray *ray, t_plane *plane,
					t_vec light_dir, double light_length);
int				cylinder_on_the_path(t_ray *ray, t_cylinder *cylinder,
					t_vec light_dir, double light_length);
int				shadow_intersect_cylinder(t_ray *ray,
					t_cylinder *cylinder, t_vec light_dir, double light_lenght);
int				shadow_intersect_sphere(t_ray *ray, t_sphere *sphere,
					t_vec light_dir, double light_lenght);
int				shadow_intersect_plane(t_ray *ray, t_plane *plane,
					t_vec light_dir, double light_lenght);
int 			shadow_intersect_quad(t_ray *ray,t_face *face,
					t_vec light_dir,double light_length);
void			set_cylinder(t_ray *ray, t_cylinder *cylinder);
void			set_shapes(t_ray *ray);
int				check_t(t_quad q, t_ray *ray, t_cylinder *cylinder,
					t_light_vec l);
/* THREADS */
void			distribute_lines_threads(t_all *all);
int				launch_threads(t_all *all);
unsigned long	get_time_diff(struct timeval *last);
t_thread_mode	get_thread_mode(t_all *all, t_threads *thread);
t_thread_mode	get_thread_mode_pause(t_all *all, t_threads *thread);
t_thread_mode	get_thread_mode_pause_reset(t_all *all, t_threads *thread);
void			*thread_routine(void *content);
void			change_threads_mode(t_all *all, t_thread_mode mode);
int				end_thread(t_all *all, unsigned int n_thread);
void			draw_rays_to_render(t_all *all, t_render *render);

/* MOVEMENTS */
int				get_key_press(t_tri_lib *lib, t_all *all);
void			get_cam_move(t_tri_lib *lib, t_all *all, int *start);
void			get_cam_rotation(t_tri_lib *lib, t_all *all, int *start);
void			get_distlight_and_fov(t_tri_lib *lib, t_all *all, int *start);
void			event_key_press(t_tri_lib *lib, void *a);
int				move_point(t_tri_lib *lib, t_coord *point,
					t_vec *dir, double amount);

/* RAYS SPECIAL */
void			iter_rays(t_all *all, t_threads *thread, void (*f)(t_ray *));
t_thread_mode	iter_rays_line_stop(t_all *all, t_threads *thread, void (*f)(t_ray *, t_all *));
void			get_closest_color(t_ray *ray, t_all *all);
void			get_diffuse_light(t_ray *ray, t_all *all);

void			intersect_cylinder(t_ray *ray, t_cylinder *cylinder);

t_hitbox		*create_bvh_iter(t_all *all, int end, int depth);
t_vec			distance_box(t_vec *a, t_vec *b);
t_bvh			create_box(t_vec a, t_vec b);
void			print_box(t_bvh *bvh);
int				intersect_hitbox(t_ray *ray, t_bvh *box);
t_shape			*create_shape_array(t_all *all);
t_bvh			box_around_two_box(t_bvh *first, t_bvh *second);
void			intersect_box(t_ray *ray, t_box *box);
int				shadow_intersect_bvh(t_ray *ray, t_bvh *box, t_vec light_dir);
int				box_on_path(t_ray *ray, t_box *boxes, t_vec light_dir);
t_hitbox		*create_bvh_triangles(t_object *obj);
t_hitbox		*create_bvh_node(t_hitbox *l, t_hitbox *r);
int				free_hitboxes(t_hitbox *root, unsigned long capacity);

void 			intersect_quad(t_ray *ray, t_face *face);

void			export_bvh_to_dot(t_hitbox *root);
unsigned long	bvh_nb_leafs(t_hitbox *root);
/* DATA STRUCTURE */
t_hitbox	*queue_free(t_queue *q);
t_hitbox	*queue_pop(t_queue *q);
int			queue_push(t_queue *q, t_hitbox *curr);
int			queue_size(t_queue *q);
int			queue_is_empty(t_queue *q);
int			queue_init(t_queue *q, int capacity);
void		queue_print(t_queue queue);

t_hitbox	*stack_free(t_stack *s);
t_hitbox	*stack_pop(t_stack *s);
int			stack_push(t_stack *s, t_hitbox *curr);
int			stack_size(t_stack *s);
int			stack_is_empty(t_stack *s);
int			stack_init(t_stack *s);

#endif
