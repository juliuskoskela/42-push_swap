#include "../inc/push_swap.h"

// Calculate the desired position for the value in stack a
// Stack a rotations are not reversed at this point so we
// need to find the zero position (smallest value) in the
// stack and calculate the position from there.

int	ps_value_target_index(t_stacks *ab, int b_val)
{
	int		*a_val;
	t_size	zero_pos;
	t_size	i;

	zero_pos = ps_stack_zero_index(ab);
	i = zero_pos;
	while (1)
	{
		a_val = arr_get(&ab->a, i);
		if (*a_val > b_val)
			return (i);
		i = (i + 1) % ab->a.len;
		if (i == zero_pos)
			break ;
	}
	return (zero_pos);
}
