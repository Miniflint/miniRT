#include "miniRT.h"
#include "tri_lib.h"

char	*readfile(int fd)
{
	ssize_t		rd;
	char	*buf;
	char	*final;
	int		i;

	final = NULL;
	i = 0;
	while (1)
	{
		rd = (BUFF_SIZE << i);
		buf = malloc(sizeof(char) * (rd + 1));
		if (!buf)
			return (printf("Error: buffer malloc\n"), NULL);
		rd = read(fd, buf, rd);
		if (!rd)
			break ;
		else if (rd == -1 && final)
			return (free(buf), free(final), NULL);
		else if (rd == -1 && !final)
			return (free(buf), NULL);
		buf[rd] = 0;
		final = ft_strjoin(final, buf);
		if (!final)
			return (free(buf), printf("Error: buffer malloc error\n"), NULL);
		free(buf);
		i += (i < 18);
	}
	free(buf);
	return (final);
}

void	event_key_press(t_tri_lib *lib, void *a)
{
	(void)a;
	if (lib->event->key_id == 'q')
		lib->destroy_window(lib->event->win_id);
}

int looped(t_tri_lib *lib, void *a)
{
	(void)a;
	if (lib->event && lib->event->type == KEY_PRESS)
		event_key_press(lib, a);
	if (lib->event && lib->event->type == MOUSE_MOVE)
		printf("AAAAA\n");
	return (0);
}

int	mouse_press(int button, int x, int y, void *param)
{
	(void)param;
	printf("%d, P(%i,%i)\n", button, x, y);
	return (0);
}
int on_configure(int x, int y, void *param)
{
	(void)param;
	printf("(%i,%i)\n", x, y);
    return 0;
}

// Dans main

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc < 2)
		return (printf("Not enough arguments\n"), 1);
	all = __get_all();
	if (__init__(all, argv, argc))
		return (free_all(all), 1);
	//print_all_structs(all);
	tri_lib()->init();
	tri_lib()->get_end_function(free_all);
	tri_lib()->_user_content = all;
	void *win = tri_lib()->create_window("QQQQQQQQQQQ", 800, 600)->_win;
	mlx_hook(win, 22, 1L << 17, on_configure, NULL);
	tri_lib()->loop(looped, all);
	return (0);
}
