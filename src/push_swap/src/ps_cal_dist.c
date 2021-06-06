# include "../inc/push_swap.h"

// Optimizes rotations in the same direction and combines them
// to composite operations for the sake of the distance calculations.

static t_rots	ps_merge_rots(t_rots rots)
{
	if (rots.a > 0)
	{
		if (rots.a > rots.b)
			rots.a -= rots.b;
		else
			rots.b -= rots.a;
	}
	else
	{
		if (rots.a < rots.b)
			rots.a -= rots.b;
		else
			rots.b -= rots.a;
	}
	return (rots);
}

// The two stacks can be thought of as two wheels with a
// zero index by which they are connected. A value has
// a current position and a desired position (where it
// fits after sorting). Distance is a combination of rotations
// in stack a, rotations in stack b and a `pb` operation to push
// the value from b stack b to stack a.

static t_rots	ps_opt_rots(t_stacks *ab, t_rots rots)
{
	int	common_rotations_org;
	int	common_rotations_rev;

	// common_rotations_org =
	if ((int)(math_abs(rots.a) + math_abs(rots.b))
		> (int)((ab->a.len - math_abs(rots.a))
		+ (ab->b.len - math_abs(rots.b)) / 2))
	{
		if (rots.a > 0)
			rots.a = (ab->a.len - rots.a) * -1;
		else
			rots.a = ab->a.len - math_abs(rots.a);
		if (rots.b > 0)
			rots.b = (ab->b.len - rots.b) * -1;
		else
			rots.b = ab->b.len - math_abs(rots.b);
	}
	return (rots);
}

static t_rots	ps_calc_rots(t_stacks *ab, int src_index)
{
	t_rots	rots;
	int		*b_val;
	int		dst_index;

	b_val = arr_get(&ab->b, src_index);
	dst_index = ps_value_target_index(ab, *b_val);
	if (src_index >= (int)(ab->b.len / 2))
		rots.b = ab->b.len - src_index;
	else
		rots.b = -src_index;
	if (dst_index >= (int)(ab->a.len / 2))
		rots.a = ab->a.len - dst_index;
	else
		rots.a = -dst_index;
	return (ps_opt_rots(ab, rots));
}

// Calculate a distance for a given value in the b-stack.
// This distance is used to choose which value to move.

int		ps_calc_dist(t_stacks *ab, t_size src_index)
{
	t_rots	rots;

	rots = ps_calc_rots(ab, src_index);
	if ((rots.a > 0 && rots.b > 0)
		|| (rots.a < 0 && rots.b < 0))
		rots = ps_merge_rots(rots);
	return (math_abs(rots.a) + math_abs(rots.b) + 1);
}
