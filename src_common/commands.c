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
	// arr_add_last(&ab->commands, "sa");
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
	// arr_add_last(&ab->commands, "sb");
}

void		ss(t_stacks *ab)
{
	sa(ab);
	sb(ab);
	// arr_add_last(&ab->commands, "ss");
}

void		pa(t_stacks *ab)
{
	int	tmp;

	arr_take_first(&tmp, &ab->b);
	arr_add_first(&ab->a, &tmp);
	// arr_add_last(&ab->commands, "pa");
}

void		pb(t_stacks *ab)
{
	int	tmp;

	arr_take_first(&tmp, &ab->a);
	arr_add_first(&ab->b, &tmp);
	// arr_add_last(&ab->commands, "pb");
}

void		ra(t_stacks *ab)
{
	arr_rotate(&ab->a, -1);
	// arr_add_last(&ab->commands, "ra");
}

void		rb(t_stacks *ab)
{
	arr_rotate(&ab->b, -1);
	// arr_add_last(&ab->commands, "rb");
}

void		rr(t_stacks *ab)
{
	ra(ab);
	rb(ab);
	// arr_add_last(&ab->commands, "rr");
}

void		rra(t_stacks *ab)
{
	arr_rotate(&ab->a, 1);
	// arr_add_last(&ab->commands, "rra");
}

void		rrb(t_stacks *ab)
{
	arr_rotate(&ab->b, 1);
	// arr_add_last(&ab->commands, "rrb");
}

void		rrr(t_stacks *ab)
{
	rra(ab);
	rrb(ab);
	// arr_add_last(&ab->commands, "rrr");
}


