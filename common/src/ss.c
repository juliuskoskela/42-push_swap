#include "../inc/common.h"

void		ss(t_stacks *ab)
{
	int	*a_top;
	int	*a_sec;
	int	*b_top;
	int	*b_sec;

	if (ab->b.len < 2 || ab->b.len < 2)
		return ;
	a_top = arr_get(&ab->b, 0);
	a_sec = arr_get(&ab->b, 1);
	mswap(a_top, a_sec, sizeof(int));
	b_top = arr_get(&ab->b, 0);
	b_sec = arr_get(&ab->b, 1);
	mswap(b_top, b_sec, sizeof(int));
}
