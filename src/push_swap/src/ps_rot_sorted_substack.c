#include "../inc/push_swap.h"

static int	ps_sorted_substack_len(t_stacks *ab, int index)
{
	int		*cur1;
	int		*cur2;
	int		sub_len;
	t_size	i;

	sub_len = 0;
	i = index;
	while (sub_len < (int)ab->a.len - 1)
	{
		cur1 = arr_get(&ab->a, i);
		cur2 = arr_get(&ab->a, (i + 1) % ab->a.len);
		if (*cur1 > *cur2)
			break ;
		i = (i + 1) % ab->a.len;
		sub_len++;
	}
	return (sub_len);
}

void	ps_rot_sorted_substack(t_stacks *ab)
{
	int		sub_len;
	int		best_len;
	int		pos;
	int		rots;
	t_size	i;

	best_len = ps_sorted_substack_len(ab, 0);
	pos = 0;
	i = 1;
	while (i < ab->a.len)
	{
		sub_len = ps_sorted_substack_len(ab, i);
		if (sub_len > best_len && (int)(ab->a.len - best_len - pos) < sub_len)
		{
			best_len = sub_len;
			pos = i;
		}
		i++;
	}
	rots = ab->a.len - (best_len + 1) - pos;
	if (rots > 0 && best_len > rots)
		ps_exec(ab, rots, RRA);
	else if (best_len > math_abs(rots))
		ps_exec(ab, math_abs(rots), RA);
}
