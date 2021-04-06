#include "../inc/push_swap.h"

void		sa(t_ab *ab)
{
	a_swap_first_two(&ab->a);
	a_add(&ab->commands, "sa");
}

void		sb(t_ab *ab)
{
	a_swap_first_two(&ab->b);
	a_add(&ab->commands, "sb");
}

void		ss(t_ab *ab)
{
	a_swap_first_two(&ab->a);
	a_swap_first_two(&ab->b);
	a_add(&ab->commands, "ss");
}

void		pa(t_ab *ab)
{
	void	*tmp;

	tmp = a_dequeue(&ab->b);
	a_insert(&ab->a, 0, tmp);
	a_add(&ab->commands, "pa");
}

void		pb(t_ab *ab)
{
	void	*tmp;

	tmp = a_dequeue(&ab->a);
	a_insert(&ab->b, 0, tmp);
	a_add(&ab->commands, "pb");
}

void		ra(t_ab *ab)
{
	a_rotate(&ab->a);
	a_add(&ab->commands, "ra");
}

void		rb(t_ab *ab)
{
	a_rotate(&ab->b);
	a_add(&ab->commands, "rb");
}

void		rr(t_ab *ab)
{
	a_rotate(&ab->a);
	a_rotate(&ab->b);
	a_add(&ab->commands, "rr");
}

void		rra(t_ab *ab)
{
	a_rev_rotate(&ab->a);
	a_add(&ab->commands, "rra");
}

void		rrb(t_ab *ab)
{
	a_rev_rotate(&ab->b);
	a_add(&ab->commands, "rrb");
}

void		rrr(t_ab *ab)
{
	a_rev_rotate(&ab->a);
	a_rev_rotate(&ab->b);
	a_add(&ab->commands, "rrr");
}

