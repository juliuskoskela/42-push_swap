#include "../inc/common.h"

void		ra(t_stacks *ab)
{
	arr_rotate(&ab->a, -1);
	parr_add_last(&ab->commands, "ra");
}
