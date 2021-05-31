#include "../inc/push_swap.h"

void		sa(t_stacks *ab)
{
	int	*top;
	int	*sec;
	int	tmp;

	if (ab->a.len < 2)
		return ;
	top = arr_get(&ab->a, 0);
	sec = arr_get(&ab->a, 1);
	tmp = *top;
	*top = *sec;
	*sec = tmp;
	arr_add_last(&ab->commands, "sa");
	print("sa\n");
}

void		sb(t_stacks *ab)
{
	int	*top;
	int	*sec;
	int	tmp;

	if (ab->b.len < 2)
		return ;
	top = arr_get(&ab->b, 0);
	sec = arr_get(&ab->b, 1);
	tmp = *top;
	*top = *sec;
	*sec = tmp;
	arr_add_last(&ab->commands, "sb");
	print("sb\n");
}

void		ss(t_stacks *ab)
{
	sa(ab);
	sb(ab);
	arr_add_last(&ab->commands, "ss");
	print("ss\n");
}

void		pa(t_stacks *ab)
{
	int	tmp;

	arr_take_first(&tmp, &ab->b);
	arr_add_first(&ab->a, &tmp);
	arr_add_last(&ab->commands, "pa");
	print("pa\n");
}

void		pb(t_stacks *ab)
{
	int	tmp;

	arr_take_first(&tmp, &ab->a);
	arr_add_first(&ab->b, &tmp);
	arr_add_last(&ab->commands, "pb");
	print("pb\n");
}

void		ra(t_stacks *ab)
{
	arr_rotate(&ab->a, -1);
	arr_add_last(&ab->commands, "ra");
	print("ra\n");
}

void		rb(t_stacks *ab)
{
	arr_rotate(&ab->b, -1);
	arr_add_last(&ab->commands, "rb");
	print("rb\n");
}

void		rr(t_stacks *ab)
{
	ra(ab);
	rb(ab);
	arr_add_last(&ab->commands, "rr");
	print("rr\n");
}

void		rra(t_stacks *ab)
{
	arr_rotate(&ab->a, 1);
	arr_add_last(&ab->commands, "rra");
	print("rra\n");
}

void		rrb(t_stacks *ab)
{
	arr_rotate(&ab->b, 1);
	arr_add_last(&ab->commands, "rrb");
	print("rrb\n");
}

void		rrr(t_stacks *ab)
{
	rra(ab);
	rrb(ab);
	arr_add_last(&ab->commands, "rrr");
	print("rrr\n");
}


