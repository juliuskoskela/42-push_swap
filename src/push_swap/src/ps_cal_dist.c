#include "../inc/push_swap.h"

// Calculate a distance for a given value in the b-stack.
// This distance is used to choose which value to move.

int	ps_calc_dist(t_stacks *ab, t_size src_index)
{
	t_rots	rots;

	rots = ps_calc_opt_rots(ab, src_index);
	rots = ps_merge_rots(rots);
	return (math_abs(rots.a) + math_abs(rots.b));
}
