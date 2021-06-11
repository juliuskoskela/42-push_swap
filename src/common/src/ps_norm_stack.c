#include "../inc/common.h"

static int	ps_find_position(t_array a, int n)
{
	int		*numptr;
	t_size	pos;
	t_size	i;

	i = 0;
	pos = 0;
	while (i < a.len)
	{
		numptr = arr_get(&a, i);
		if (*numptr < n)
			pos++;
		i++;
	}
	return (pos);
}

t_array	ps_norm_stack(t_array raw)
{
	t_array	out;
	int		*n;
	int		pos;
	t_size	i;

	out = arr_new(1, sizeof(int));
	i = 0;
	while (i < raw.len)
	{
		n = arr_get(&raw, i);
		pos = ps_find_position(raw, *n);
		arr_add_last(&out, &pos);
		i++;
	}
	return (out);
}
