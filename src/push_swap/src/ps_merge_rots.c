# include "../inc/push_swap.h"

t_rots	ps_merge_rots(t_rots rots)
{
	if ((rots.a > 0 && rots.b < 0) || (rots.a < 0 && rots.b > 0))
		return (rots);
	if (rots.a > 0)
	{
		if (rots.a > rots.b)
		{
			rots.a -= rots.b;
			rots.b = 0;
		}
		else
		{
			rots.b -= rots.a;
			rots.a = 0;
		}
	}
	else
	{
		if (rots.a < rots.b)
		{
			rots.a = -((math_abs(rots.a) - math_abs(rots.b)));
			rots.b = 0;
		}
		else
		{
			rots.b = -((math_abs(rots.b) - math_abs(rots.a)));
			rots.a = 0;
		}
	}
	return (rots);
}
