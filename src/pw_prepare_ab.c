#include "../inc/push_swap.h"

static int		cmp_atoi(void *a, void *b)
{
	const char *ai;
	const char *bi;

	ai = a;
	bi = b;
	if (!a)
		return (SMALLER);
	if (!b)
		return (LARGER);
	if (atoi(ai) > atoi(bi))
		return (LARGER);
	else
		return (SMALLER);
}

static int				find_pos(t_arr a, char *item)
{
	size_t		i;
	size_t		pos;

	i = 0;
	pos = 0;
	while (i < a.count)
	{
		if (cmp_atoi(item, a.data[i]) == LARGER)
			pos++;
		i++;
	}
	return (pos);
}

static t_arr		normalize_arr(t_arr arr)
{
	t_arr		out;
	int			*numptr;
	size_t		i;

	out = a_alloc(arr.size);
	i = 0;
	while (i < arr.count)
	{
		numptr = (int *)malloc(sizeof(int));
		*numptr = find_pos(arr, arr.data[i]);
		a_add(&out, numptr);
		i++;
	}
	return (out);
}

static t_ab		new(size_t size)
{	
	t_ab	ab;

	ab.a = a_alloc(1);
	ab.b = a_alloc(1);
	ab.commands = a_alloc(1);
	ab.stack_size = size;
	return (ab);
}

t_ab		pw_prepaper_ab(int argc, char **argv)
{
	t_ab	ab;
	t_arr	args;

	ab = new(argc - 1);
	args = a_alloc(1);
	a_assign(&args, (void **)argv + 1, argc - 1);
	ab.a = normalize_arr(args);
	return (ab);
}
