#include "../inc/common.h"

void	sb(t_stacks *ab)
{
	int	*top;
	int	*sec;

	if (ab->b.len < 2)
		return ;
	top = arr_get(&ab->b, 0);
	sec = arr_get(&ab->b, 1);
	mswap(top, sec, sizeof(int));
	parr_add_last(&ab->commands, "sb");
}
