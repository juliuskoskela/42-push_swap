#include "../inc/push_swap.h"

void			pw_print_stacks(t_ab ab)
{	
	printf("\n\nA: ");
	a_iter(&ab.a, pw_print_int);
	printf("\n\nB: ");
	a_iter(&ab.b, pw_print_int);
	printf("\n\nCommands: %zu\n\n", ab.commands.count);
	a_iter(&ab.commands, pw_print_str);
}

size_t			pw_sum(t_arr *arr, size_t count)
{
	size_t		i;
	size_t		res;
	int			*ptr;

	i = 0;
	res = 0;
	while (i < arr->count && i < count)
	{
		ptr = arr->data[i];
		res += *ptr;
		i++;
	}
	return (res);
}

int				pw_find_pos(t_arr a, int *item)
{
	size_t		i;
	size_t		pos;

	i = 0;
	pos = 0;
	while (i < a.count)
	{
		if (pw_cmp(item, a.data[i]) == LARGER)
			pos++;
		i++;
	}
	return (pos);
}

t_arr			pw_norm_arr(t_arr arr)
{
	t_arr		out;
	int			*numptr;
	size_t		i;

	out = a_alloc(arr.size);
	i = 0;
	while (i < arr.count)
	{
		numptr = (int *)malloc(sizeof(int));
		*numptr = pw_find_pos(arr, arr.data[i]);
		a_add(&out, numptr);
		i++;
	}
	return (out);
}

t_ab			pw_new_ab(size_t size)
{	
	t_ab		ab;

	ab.a = a_alloc(1);
	ab.b = a_alloc(1);
	ab.partitions = a_alloc(1);
	ab.commands = a_alloc(1);
	ab.stack_size = size;
	return (ab);
}

t_ab			pw_prepaper_ab(int argc, char **argv)
{
	t_ab		ab;
	t_arr		args;

	ab = pw_new_ab(argc - 1);
	args = a_alloc(1);
	a_assign(&args, (void **)argv + 1, argc - 1);
	ab.a = pw_norm_arr(args);
	return (ab);
}

void			pw_print_str(void **data, size_t i)
{
	char		*str;

	i++;
	if (*data == NULL)
		return ;
	str = *data;
	printf("%s\n", str);
}

void			pw_print_int(void **data, size_t i)
{
	int			*num;

	if (*data == NULL)
		return ;
	num = *data;
	printf("[%zu] %d ", i, *num);
}

int				pw_cmp(void *a, void *b)
{
	const int	*ai;
	const int	*bi;

	ai = a;
	bi = b;
	if (!a)
		return (SMALLER);
	if (!b)
		return (LARGER);
	if (*ai > *bi)
		return (LARGER);
	else
		return (SMALLER);
}

int				pw_check(t_arr a)
{
	size_t		i;

	i = 1;
	while (i < a.count)
	{
		if (pw_cmp(a.data[i], a.data[i - 1]) == SMALLER)
			return (0);
		i++;
	}
	return (1);
}

