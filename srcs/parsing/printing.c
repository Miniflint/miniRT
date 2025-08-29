#include "miniRT.h"

void	print_ac(t_amb_light *ambient_light, t_cam *camera)
{
	printf("AMBIENT LIGHT:\n");
	printf("\tRatio: %f\n", ambient_light->ratio);
	printf("\tRGB: %d %d %d\n",
		ambient_light->rgb.r, ambient_light->rgb.g, ambient_light->rgb.b);
	printf("CAMERA:\n");
	printf("\tViewpoint: %f %f %f\n",
		camera->viewpoint.x, camera->viewpoint.y, camera->viewpoint.z);
	printf("\tVec: %f %f %f\n", camera->dir.x, camera->dir.y, camera->dir.z);
	printf("\tFOV: %f\n", camera->fov);
}

void	print_l(t_light *light, int depth)
{
	if (!light)
		return ;
	if (!depth)
		printf("LIGHTS:\n");
	printf("\tCoord: %f %f %f\n",
		light->coord.x, light->coord.y, light->coord.z);
	printf("\tRatio: %f\n", light->ratio);
	printf("\tRGB: %d %d %d\n",
		light->rgb.r, light->rgb.g, light->rgb.b);
	printf("\t------------------------------------\n");
	print_l(light->next, depth + 1);
}

void	print_sp(t_sphere *sphere, int depth)
{
	if (!sphere)
		return ;
	if (!depth)
		printf("SPHERES:\n");
	printf("\tCoord: %f %f %f\n",
		sphere->coord.x, sphere->coord.y, sphere->coord.z);
	printf("\tRadius: %f\n", sphere->radius * 2);
	printf("\tRGB: %d %d %d\n",
		sphere->rgb_save.r, sphere->rgb_save.g, sphere->rgb_save.b);
	printf("     ---------------------------------------------------\n");
	print_sp(sphere->next, depth + 1);
}

void	print_pl(t_plane *plane, int depth)
{
	if (!plane)
		return ;
	if (!depth)
		printf("PLANES:\n");
	printf("\tCoord: %f %f %f\n",
		plane->coord.x, plane->coord.y, plane->coord.z);
	printf("\tVec: %f %f %f\n",
		plane->vec.x, plane->vec.y, plane->vec.z);
	printf("\tRGB: %d %d %d\n",
		plane->rgb_save.r, plane->rgb_save.g, plane->rgb_save.b);
	printf("     ---------------------------------------------------\n");
	print_pl(plane->next, depth + 1);
}

void	print_cy(t_cylinder *cylinder, int depth)
{
	if (!cylinder)
		return ;
	if (!depth)
		printf("CYLINDERS:\n");
	printf("\tCoord: %f %f %f\n",
		cylinder->coord.x, cylinder->coord.y, cylinder->coord.z);
	printf("\tDiameter: %f\n", cylinder->diameter);
	printf("\tHeight: %f\n", cylinder->height);
	printf("\tRGB: %d %d %d\n",
		cylinder->rgb_save.r, cylinder->rgb_save.g, cylinder->rgb_save.b);
	printf("     ---------------------------------------------------\n");
	print_cy(cylinder->next, depth + 1);
}

void	print_vertice(t_object *object)
{
	unsigned long	i;

	i = 0;
	printf("===============   VERTICES   ================\n");
	while (i < object->nb_vertices)
	{
		printf("\t%li: %p\n", i + 1, &(object->vertices[i]));
		i++;
	}
	i = 0;
	printf("===========   VERTICES TEXTURE   ============\n");
	while (i < object->nb_vt)
	{
		printf("\t%li: %p\n", i + 1, &(object->vt[i]));
		i++;
	}
	i = 0;
	printf("===========   VERTICES NORMALE  ============\n");
	while (i < object->nb_vn)
	{
		printf("\t%li: %p\n", i + 1, &(object->vn[i]));
		i++;
	}
}

void	print_ob(t_object *object, int depth)
{
	unsigned long	i;
	int				j;

	i = 0;
	if (!object)
		return ;
	printf("Object: %s | %i\n", object->path, depth);
	print_vertice(object);
	printf("===============   FACES   ================\n");
	while (i < object->nb_faces)
	{
		j = -1;
		printf("%li - is wrong %d - smoothing: %d - group: %s:\n\t", i + 1,
			object->faces[i].is_wrong, object->faces[i].smoothing, object->faces[i].group);
		while (++j < 4)
			printf("%i:(%ld) %p ", j + 1, object->faces[i].v_indexes[j] + 1, (object->faces[i].vertices[j]));
		j = -1;
		printf("\n\t");
		while (++j < 4)
			printf("%i:(%ld) %p ", j + 1, object->faces[i].vt_indexes[j] + 1, (object->faces[i].v_texture[j]));
		j = -1;
		printf("\n\t");
		while (++j < 4)
			printf("%i:(%ld) %p ", j + 1, object->faces[i].vn_indexes[j] + 1, (object->faces[i].v_normale[j]));
		printf("\n");
		i++;
	}
	print_ob(object->next, depth + 1);
}