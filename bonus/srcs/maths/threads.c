#include "miniRT.h"

// all->canvas.pixel_values

int	launch_threads(t_all *all)
{
	unsigned int	i;
	unsigned int	n_lines;
	// unsigned int	actual_line;

	all->n_thread = sysconf(_SC_NPROCESSORS_ONLN) - 1;
	if (all->n_thread)
		return (1);
	all->threads = malloc(all->n_thread * sizeof(t_threads));
	if (!all->threads)
		return (1);
	pthread_mutex_init(&all->mutex, NULL);
	i = 0;
	n_lines = WIN_HEIGHT_ALL / all->n_thread;
	// actual_line = 0;
	while (i < all->n_thread)
	{
		all->threads[i].start = i * n_lines;
		if (i + 1 == all->n_thread)
			all->threads[i].end = WIN_HEIGHT_ALL - 1;
		else
			all->threads[i].end = all->threads->start + n_lines - 1;
		all->threads[i].mode = NONE;
		all->threads[i].average_time = 0;
		++i;
	}
	return (0);
}