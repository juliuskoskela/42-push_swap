#include "../inc/common.h"

void		pa(t_stacks *ab)
{
	int	tmp;

	arr_take_first(&tmp, &ab->b);
	arr_add_first(&ab->a, &tmp);
	parr_add_last(&ab->commands, "pa");
}
