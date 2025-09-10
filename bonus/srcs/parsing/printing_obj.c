#include "miniRT.h"

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

void	print_faces(t_face *face)
{
	int	j;

	j = -1;
	while (++j < 4)
		printf("%i:(%ld) %p ", j + 1, face->v_indexes[j] + 1,
			(face->vertices[j]));
	printf("\n\t");
	j = -1;
	while (++j < 4)
		printf("%i:(%ld) %p ", j + 1, face->vt_indexes[j] + 1,
			(face->v_texture[j]));
	printf("\n\t");
	j = -1;
	while (++j < 4)
		printf("%i:(%ld) %p ", j + 1, face->vn_indexes[j] + 1,
			(face->v_normale[j]));
	printf("\n\t");
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
		print_faces(&object->faces[i]);
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