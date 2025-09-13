#include "miniRT.h"

void	print_vec(t_vec v)
{
	printf("(%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
}

void	print_vertice(t_object *object)
{
	unsigned long	i;

	i = 0;
	printf("===============   VERTICES   ================\n");
	while (i < object->nb_vertices)
	{
		printf("\tV   %li: %p | ", i + 1, &(object->vertices[i]));
		print_vec(object->vertices[i]);
		i++;
	}
	i = 0;
	printf("===========   VERTICES TEXTURE   ============\n");
	while (i < object->nb_vt)
	{
		printf("\tv_t %li: %p | ", i + 1, &(object->vt[i]));
		print_vec(object->vt[i]);
		i++;
	}
	i = 0;
	printf("===========   VERTICES NORMALE  ============\n");
	while (i < object->nb_vn)
	{
		printf("\tv_n %li: %p | ", i + 1, &(object->vn[i]));
		print_vec(object->vn[i]);
		i++;
	}
}

void	print_faces(t_face *face, unsigned long i)
{
	int	j;

	j = -1;
	printf("Face: %li\n\t", i);
	while (++j < 4)
		printf("V   %i:(%ld) %p ", j + 1, face->v_indexes[j] + 1,
			(face->vertices[j]));
	printf("\n\t");
	j = -1;
	while (++j < 4)
		printf("v_t %i:(%ld) %p ", j + 1, face->vt_indexes[j] + 1,
			(face->v_texture[j]));
	printf("\n\t");
	j = -1;
	while (++j < 4)
		printf("v_n %i:(%ld) %p ", j + 1, face->vn_indexes[j] + 1,
			(face->v_normale[j]));
}

void	print_ob(t_object *object, int depth)
{
	unsigned long	i;

	i = 0;
	if (!object)
		return ;
	printf("Object: %s | %i\n", object->path, depth);
	print_vertice(object);
	printf("===============   FACES   ================\n");
	while (i < object->nb_faces)
	{
		print_faces(&object->faces[i], i);
		printf("\n");
		i++;
	}
	print_ob(object->next, depth + 1);
}

void	print_bx(t_box *box, int depth)
{
	if (!box)
		return ;
	if (!depth)
		printf("BOXES:\n");
	print_box(&box->box);
	print_bx(box->next, depth + 1);
}