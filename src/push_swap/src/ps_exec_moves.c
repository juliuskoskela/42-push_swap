#include "../inc/push_swap.h"

static t_rots	ps_exec_rrr(t_stacks *ab, t_rots rots)
{	
	if (rots.a > rots.b)
	{
		ps_exec(ab, rots.b, RRR);
		rots.a -= rots.b;
		rots.b = 0;
	}
	else
	{
		ps_exec(ab, rots.a, RRR);
		rots.b -= rots.a;
		rots.a = 0;
	}
	return (rots);
}

static t_rots	ps_exec_rr(t_stacks *ab, t_rots rots)
{
	if (rots.a < rots.b)
	{
		ps_exec(ab, math_abs(rots.b), RR);
		rots.a = -((math_abs(rots.a) - math_abs(rots.b)));
		rots.b = 0;
	}
	else
	{
		ps_exec(ab, math_abs(rots.a), RR);
		rots.b = -((math_abs(rots.b) - math_abs(rots.a)));
		rots.a = 0;
	}
	return (rots);
}

static t_rots	ps_exec_merge_rots(t_stacks *ab, t_rots rots)
{
	if (rots.a > 0)
		rots = ps_exec_rrr(ab, rots);
	else
		rots = ps_exec_rr(ab, rots);
	return (rots);
}

void	ps_exec_moves(t_stacks *ab, t_rots rots)
{
	if ((rots.a > 0 && rots.b > 0)
		|| (rots.a < 0 && rots.b < 0))
		rots = ps_exec_merge_rots(ab, rots);
	if (rots.b > 0)
		ps_exec(ab, rots.b, RRB);
	else
		ps_exec(ab, math_abs(rots.b), RB);
	if (rots.a > 0)
		ps_exec(ab, rots.a, RRA);
	else
		ps_exec(ab, math_abs(rots.a), RA);
	ps_exec(ab, 1, PA);
}
