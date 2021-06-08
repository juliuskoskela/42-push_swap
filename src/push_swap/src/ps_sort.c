# include "../inc/push_swap.h"

static int	check_case(t_array *arr)
{
	int	*v1;
	int	*v2;
	int	*v3;

	v1 = arr_get(arr, 0);
	v2 = arr_get(arr, 1);
	v3 = arr_get(arr, 2);
	if (*v1 > *v2 && *v2 > *v3)
		return (1);
	else if (*v1 > *v2 && *v2 < *v3 && *v3 > *v1)
		return (2);
	else if (*v1 < *v2 && *v2 > *v3 && *v3 > *v1)
		return (3);
	else if (*v1 > *v2 && *v2 < *v3 && *v3 < *v1)
		return (4);
	else if (*v1 < *v2 && *v2 > *v3 && *v3 < *v1)
		return (5);
	else if (*v1 < *v2 && *v2 < *v3)
		return (6);
	return (0);
}

static void	ps_sort_last3_in_a(t_stacks *ab)
{
	int	case3;

	case3 = check_case(&ab->a);
	if (case3 == 6)
		return ;
	else if (case3 == 5)
		rra(ab);
	else if (case3 == 4)
		ra(ab);
	else if (case3 == 3)
	{
		sa(ab);
		ra(ab);
	}
	else if (case3 == 2)
		sa(ab);
	else if (case3 == 1)
	{
		sa(ab);
		rra(ab);
	}
}

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

static void	ps_rot_sorted_substack(t_stacks *ab)
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

static void	ps_split(t_stacks *ab, int len)
{
	int	*a_top;
	int	*a_bot;
	int	i;

	ps_rot_sorted_substack(ab);
	i = 0;
	while (i < len)
	{
		a_top = arr_get_first(&ab->a);
		a_bot = arr_get_last(&ab->a);
		if (ps_sorted(ab->a) == TRUE)
			break ;
		if (*a_top > *a_bot)
			ra(ab);
		pb(ab);
		i++;
	}
}

void	ps_sort(t_stacks *ab)
{
	int	*top;
	int	*sec;

	if (ab->a.len > 3)
		ps_split(ab, ab->a.len - 3);
	if (ab->a.len == 3)
		ps_sort_last3_in_a(ab);
	if (ab->a.len == 2)
	{
		top = arr_get(&ab->a, 0);
		sec = arr_get(&ab->a, 1);
		if (*top > *sec)
			sa(ab);
		return ;
	}
	if (ab->b.len > 0)
		ps_merge(ab);
}
