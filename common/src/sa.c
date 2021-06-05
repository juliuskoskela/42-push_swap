#include "../inc/common.h"

void		sa(t_stacks *ab)
{
	int	*top;
	int	*sec;

	if (ab->a.len < 2)
		return ;
	top = arr_get(&ab->a, 0);
	sec = arr_get(&ab->a, 1);
	mswap(top, sec, sizeof(int));
	parr_add_last(&ab->commands, "sa");
}