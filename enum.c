#include "array/inc/array.h"
# define LARGER 1
# define SMALLER -1
# define A_EMPTY -2
# define B_EMPTY -3














int			cmp(void *a, void *b)
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






int				find_pos(t_arr a, char *item)
{
	size_t		i;
	size_t		pos;

	i = 0;
	pos = 0;
	while (i < a.count)
	{
		if (cmp(item, a.data[i]) == LARGER)
			pos++;
		i++;
	}
	return (pos);
}

void		print(void **data, size_t i)
{
	char	*str;

	if (*data == NULL)
		return ;
	str = *data;
	printf("%-3s ", str);
}

void		print_int(void **data, size_t i)
{
	int		*num;

	if (*data == NULL)
		return ;
	num = *data;
	printf("%d ", *num);
}

t_arr		normalize_arr(t_arr *arr)
{
	t_arr		out;
	int			*numptr;
	size_t		i;

	out = a_alloc(arr->size);
	i = 0;
	i = 0;
	while (i < arr->count)
	{
		numptr = (int *)malloc(sizeof(int));
		*numptr = find_pos(*arr, arr->data[i]);
		a_add(&out, numptr);
		i++;
	}
	return (out);
}

int				main(int argc, char **argv)
{
	t_arr		arr;

	arr = a_alloc(1);
	a_assign(&arr, (void **)argv + 1, argc - 1);
	normalize_arr(&arr);
	t_arr ret = normalize_arr(&arr);
	a_dalloc(&arr);
	arr = ret;
	a_iter(&arr, print_int);
}


