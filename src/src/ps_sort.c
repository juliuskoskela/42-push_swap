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

static void	ps_split(t_stacks *ab, int len)
{
	int *a_top;
	int *a_bot;
	int *b_top;
	int *b_bot;
	int	i;

	i = 0;
	while (i < len)
	{
		a_top = arr_get_first(&ab->a);
		a_bot = arr_get_last(&ab->a);
		if (*a_top > *a_bot)
		{
			if (ab->b.len > 2)
			{
				b_top = arr_get_first(&ab->a);
				b_bot = arr_get_last(&ab->a);
				if (*b_top < *b_bot)
					rr(ab);
			}
			else
				ra(ab);
		}
		if (ps_sorted(ab->a) == TRUE)
			break ;
		ps_exec(ab, 1, PB);
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