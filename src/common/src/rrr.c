#include "../inc/common.h"

void	rrr(t_stacks *ab)
{
	arr_rotate(&ab->a, 1);
	arr_rotate(&ab->b, 1);
	parr_add_last(&ab->commands, "rrr");
}
