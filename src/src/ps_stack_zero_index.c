# include "../inc/push_swap.h"

// Get the smallest value position in stack a.

int	ps_stack_zero_index(t_stacks *ab)
{
	int		*val_1;
	int		*val_2;
	t_size	i;

	i = ab->a.len - 1;
	while (i > 0)
	{
		val_1 = arr_get(&ab->a, i);
		val_2 = arr_get(&ab->a, i - 1);
		if (*val_1 < *val_2)
			return (i);
		i--;
	}
	return (0);
}
