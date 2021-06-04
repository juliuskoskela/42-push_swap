#include "../inc/push_swap.h"

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

void		sb(t_stacks *ab)
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

void		pa(t_stacks *ab)
{
	int	tmp;

	arr_take_first(&tmp, &ab->b);
	arr_add_first(&ab->a, &tmp);
	parr_add_last(&ab->commands, "pa");
}

void		pb(t_stacks *ab)
{
	int	tmp;

	arr_take_first(&tmp, &ab->a);
	arr_add_first(&ab->b, &tmp);
	parr_add_last(&ab->commands, "pb");
}

void		ra(t_stacks *ab)
{
	arr_rotate(&ab->a, -1);
	parr_add_last(&ab->commands, "ra");
}

void		rb(t_stacks *ab)
{
	arr_rotate(&ab->b, -1);
	parr_add_last(&ab->commands, "rb");
}

void		rr(t_stacks *ab)
{
	arr_rotate(&ab->a, -1);
	arr_rotate(&ab->b, -1);
	parr_add_last(&ab->commands, "rr");
}

void		rra(t_stacks *ab)
{
	arr_rotate(&ab->a, 1);
	parr_add_last(&ab->commands, "rra");
}

void		rrb(t_stacks *ab)
{
	arr_rotate(&ab->b, 1);
	parr_add_last(&ab->commands, "rrb");
}

void		rrr(t_stacks *ab)
{
	arr_rotate(&ab->a, 1);
	arr_rotate(&ab->b, 1);
	parr_add_last(&ab->commands, "rrr");
}


