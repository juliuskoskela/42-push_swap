#include "../inc/push_swap.h"

static int		check_case3(t_arr *arr)
{
	int			*v1;
	int			*v2;
	int			*v3;

	v1 = a_get(arr, 0);
	v2 = a_get(arr, 1);
	v3 = a_get(arr, 2);
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

void			pw_sort3a(t_ab *ab)
{
	int			*v1;
	int			*v2;
	int			*v3;

	v1 = a_get(&ab->a, 0);
	v2 = a_get(&ab->a, 1);
	v3 = a_get(&ab->a, 2);
	if (*v1 < *v2 && *v2 < *v3)
		return ;
	else if (*v1 < *v2 && *v2 > *v3 && *v1 < *v3)
	{
		ra(ab);
		sa(ab);
		rra(ab);
	}
	else if (*v1 > *v2 && *v2 < *v3 && *v1 < *v3)
	{
		sa(ab);
	}
	else if (*v1 < *v2 && *v2 > *v3)
	{
		ra(ab);
		sa(ab);
		rra(ab);
		sa(ab);
	}
	else if (*v1 > *v2 && *v2 < *v3 && *v1 > *v3)
	{
		sa(ab);
		ra(ab);
		sa(ab);
		rra(ab);
	}
	else if (*v1 > *v2 && *v2 > *v3 && *v1 > *v3)
	{
		sa(ab);
		ra(ab);
		sa(ab);
		rra(ab);
		sa(ab);
	}
}

void			pw_sort3b(t_ab *ab)
{
	int			*v1;
	int			*v2;
	int			*v3;

	v1 = a_get(&ab->b, 0);
	v2 = a_get(&ab->b, 1);
	v3 = a_get(&ab->b, 2);
	if (*v1 > *v2 && *v2 > *v3)
		return ;
	else if (*v1 > *v2 && *v2 < *v3 && *v1 > *v3)
	{
		rb(ab);
		sb(ab);
		rrb(ab);
	}
	else if (*v1 < *v2 && *v2 > *v3 && *v1 > *v3)
	{
		sb(ab);
	}
	else if (*v1 > *v2 && *v2 < *v3 && *v1 < *v3)
	{
		rb(ab);
		sb(ab);
		rrb(ab);
		sb(ab);
	}
	else if (*v1 < *v2 && *v2 > *v3 && *v1 < *v3)
	{
		sb(ab);
		rb(ab);
		sb(ab);
		rrb(ab);
	}
	else if (*v1 < *v2 && *v2 < *v3 && *v1 < *v3)
	{
		sb(ab);
		rb(ab);
		sb(ab);
		rrb(ab);
		sb(ab);
	}
}

void            pw_sort3a_simple(t_ab *ab)
{
    int            case3;

    case3 = check_case3(&ab->a);
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

void            pw_sort3b_simple(t_ab *ab)
{
    int            case3;

    case3 = check_case3(&ab->a);
    if (case3 == 1)
        return ;
    else if (case3 == 2)
        rrb(ab);
    else if (case3 == 3)
        rb(ab);
    else if (case3 == 4)
    {
        sb(ab);
        rb(ab);
    }
    else if (case3 == 5)
        sb(ab);
    else if (case3 == 6)
    {
        sb(ab);
        rrb(ab);
    }
}

size_t			pw_split_from_pivot_a(t_ab *ab, int pivot, size_t part_size)
{
	int			*top;
	int			*second;
	int			*bottom;
	size_t		i;
	size_t		out;

	i = 0;
	out = 0;
	while (i < part_size)
	{
		top = a_get(&ab->a, 0);
		second = a_get(&ab->a, 1);
		bottom = a_peek(&ab->a);
		if (*top < pivot)
		{
			pb(ab);
			out++;
		}
		else if (*bottom < pivot)
			rra(ab);
		else if (*second < pivot)
			sa(ab);
		else
			ra(ab);
		i++;
	}
	i = 0;
	/*while (i++ < part_size - out)*/
		/*rra(ab);*/
	return (out);
}

size_t			pw_split_from_pivot_b(t_ab *ab, int pivot, size_t part_size)
{
	int			*top;
	int			*second;
	int			*bottom;
	size_t		i;
	size_t		out;

	i = 0;
	out = 0;
	while (i < part_size)
	{
		top = a_get(&ab->b, 0);
		second = a_get(&ab->b, 1);
		bottom = a_peek(&ab->b);
		if (*top > pivot)
		{
			pa(ab);
			out++;
		}
		else if (*bottom > pivot)
			rrb(ab);
		else if (*second > pivot)
			sb(ab);
		else
			rb(ab);
		i++;
	}
	i = 0;
	/*while (i++ < part_size - out)*/
		/*rrb(ab);*/
	return (out);
}

void			pw_sort_b(t_ab *ab, size_t b_part)
{
	int			pivot;
	size_t		tmp;

	tmp = 0;
	pw_print_stacks(*ab);
	if (b_part > 3)
	{
		pivot = pw_sum(&ab->b, b_part) / b_part;
		tmp = pw_split_from_pivot_b(ab, pivot, b_part);
		printf("\n\npivot_b: %d\n", pivot);
		printf("\npivot_tmp_b: %d", (int)tmp);
		pw_sort_b(ab, b_part - tmp);
		pw_sort_a(ab, tmp);
	}
	if (b_part == ab->b.count && b_part == 3)
		pw_sort3b_simple(ab);
	else if (b_part == 3)
		pw_sort3b(ab);
	else if (b_part == 2 && pw_cmp(ab->b.data[0], ab->b.data[1]) == SMALLER)
		sb(ab);
	while (tmp--)
		pb(ab);
}

void			pw_sort_a(t_ab *ab, size_t a_part)
{
	int			pivot;
	size_t		tmp;

	tmp = 0;
	pw_print_stacks(*ab);
	if (a_part > 3)
	{
		pivot = pw_sum(&ab->a, a_part) / a_part;
		tmp = pw_split_from_pivot_a(ab, pivot, a_part);
		printf("\n\npivot_a: %d\n", pivot);
		printf("\npivot_tmp_a: %d", (int)tmp);
		pw_sort_a(ab, a_part - tmp);
		pw_sort_b(ab, tmp);
	}
	if (a_part == ab->a.count && a_part == 3)
		pw_sort3a_simple(ab);
	if (a_part == 3)
		pw_sort3a(ab);
	else if (a_part == 2 && pw_cmp(ab->a.data[0], ab->a.data[1]) == LARGER)
		sa(ab);
	while (tmp--)
		pa(ab);
}

int				main(int argc, char **argv)
{
	t_ab		ab;
	t_arr		args;

	args = a_alloc(100);
	a_readfile(&args, argv[1]);
	ab = pw_prepaper_ab(args.count, (char **)args.data);
	pw_sort_a(&ab, ab.stack_size);
	pw_print_stacks(ab);
	printf("\nsorted: %d", pw_check(ab.a));
}
