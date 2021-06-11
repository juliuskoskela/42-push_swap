#include "../inc/push_swap.h"

static t_size	ps_choose_val_in_b(t_stacks *ab)
{
	int		tmp;
	int		ret;
	t_size	pos;
	t_size	i;

	ret = ps_calc_dist(ab, 0);
	pos = 0;
	i = 1;
	while (i < ab->b.len)
	{
		tmp = ps_calc_dist(ab, i);
		if (tmp < ret)
		{
			ret = tmp;
			pos = i;
		}
		i++;
	}
	return (pos);
}

static void	ps_rot_back(t_stacks *ab)
{
	int		index;

	index = ps_stack_zero_index(ab);
	if (index >= (int)(ab->a.len / 2))
		ps_exec(ab, ab->a.len - index, RRA);
	else
		ps_exec(ab, index, RA);
}

void	ps_merge(t_stacks *ab)
{
	t_rots	rots;
	t_size	src_index;

	while (ab->b.len)
	{
		src_index = ps_choose_val_in_b(ab);
		rots = ps_calc_opt_rots(ab, src_index);
		ps_exec_moves(ab, rots);
	}
	ps_rot_back(ab);
}
