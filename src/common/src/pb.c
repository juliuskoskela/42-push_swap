#include "../inc/common.h"

void	pb(t_stacks *ab)
{
	int	tmp;

	arr_take_first(&tmp, &ab->a);
	arr_add_first(&ab->b, &tmp);
	parr_add_last(&ab->commands, "pb");
}
