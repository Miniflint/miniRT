#include "miniRT.h"

int	get_box(t_box **head, char **const restrict s)
{
	t_box	*const	box = create_empty_node(sizeof(t_box) * 1);

	if (!box)
		return (1);
	if (skip_till_number(s, 2))
		return (free(box), 3);
	if (get_coord(&box->box.bottom[0], s))
		return (free(box), printf("\tboxs problem\n"), 1);
	if (skip_till_number(s, 0))
		return (free(box), 3);
	if (get_coord(&box->box.top[3], s))
		return (free(box), printf("\tboxs problem\n"), 1);
	if (skip_till_number(s, 0))
		return (free(box), 3);
	if (get_rgb(&box->rgb_save, s))
		return (free(box), printf("\tboxs problem\n"), 1);
	if (get_material(&box->material, s))
		return (3);
	box->color = argb_to_rgbf(box->rgb_save);
	box->box = create_box(box->box.bottom[0], box->box.top[3]);
	box->box.a = &box->box.bottom[0];
	box->box.b = &box->box.top[3];
	box->next = *head;
	*head = box;
	if (!**s)
		return (2);
	return (skip_whitespace_hashtag(s, &(__get_all()->line_count)));
}
