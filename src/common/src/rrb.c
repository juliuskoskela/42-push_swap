#include "../inc/common.h"

void	rrb(t_stacks *ab)
{
	arr_rotate(&ab->b, 1);
	parr_add_last(&ab->commands, "rrb");
}
