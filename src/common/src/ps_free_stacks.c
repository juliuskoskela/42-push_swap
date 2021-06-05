#include "../inc/common.h"

void	ps_free_stacks(t_stacks ab)
{
	arr_free(&ab.a);
	arr_free(&ab.b);
	parr_free(&ab.commands);
}
