# include "../inc/push_swap.h"

static int	ps_calc_merged_dist(t_rots rots)
{
	rots = ps_merge_rots(rots);
	return (math_abs(rots.a) + math_abs(rots.b));
}

static void ps_rot_cases(t_rots *cases, t_stacks *ab, int dst_index, int src_index)
{
	cases[0].a = ab->a.len - dst_index;
	cases[0].b = ab->b.len - src_index;
	cases[1].a = -dst_index;
	cases[1].b = -src_index;
	cases[2].a = ab->a.len - dst_index;
	cases[2].b = -src_index;
	cases[3].a = -dst_index;
	cases[3].b = ab->b.len - src_index;
}

static t_rots	ps_opt_rots(t_stacks *ab, int dst_index, int src_index)
{
	int		distance;
	int		best;
	t_rots	out;
	t_rots	cases[4];
	t_size	i;

	ps_rot_cases(cases, ab, dst_index, src_index);
	best = ps_calc_merged_dist(cases[0]);
	out = cases[0];
	i = 1;
	while (i < 4)
	{
		distance = ps_calc_merged_dist(cases[i]);
		if (distance < best)
		{
			best = distance;
			out = cases[i];
		}
		i++;
	}
	return (out);
}

t_rots	ps_calc_opt_rots(t_stacks *ab, int src_index)
{
	int		*b_val;
	int		dst_index;

	b_val = arr_get(&ab->b, src_index);
	dst_index = ps_value_target_index(ab, *b_val);
	return (ps_opt_rots(ab, dst_index, src_index));
}
