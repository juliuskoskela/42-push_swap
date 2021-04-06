#include "../inc/push_swap.h"

static int		check_case(t_arr *arr)
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

void            pw_sort_last3_in_b(t_ab *ab)
{
    int            case3;

    case3 = check_case(&ab->b);
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

void            pw_sort_last3_in_a(t_ab *ab)
{
    int            case3;

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

size_t			pw_get_pivot(t_arr *arr)
{
	size_t		i;
	size_t		res;
	int			*ptr;

	i = 0;
	res = 0;
	while (i < arr->count)
	{
		ptr = arr->data[i];
		res += *ptr;
		i++;
	}
	return (res / arr->count);
}

int				pw_get_direction_in_a(t_ab *ab, int pivot)
{
	int			i;
	int			j;
	int			*a_val_i;
	int			*a_val_j;
	
	i = 0;
	while (i < (int)ab->a.count)
	{
		a_val_i = a_get(&ab->a, i);
		if (*a_val_i < pivot)
			break ;
		i++;
	}
	j = ab->a.count - 1;
	while (j > 0)
	{
		a_val_j = a_get(&ab->a, j);
		if (*a_val_j < pivot)
			break ;
		j--;
	}
	j = ab->a.count - j;
	if (i < j)
		return (1);
	else
		return (0);
}

void			pw_split_from_pivot(t_ab *ab, int pivot)
{
	int			*top;
	int			i;

	i = ab->a.count;
	while (i--)
	{
		top = a_get(&ab->a, 0);
		if (*top < pivot)
			pb(ab);
		else
			ra(ab);
	}
}

void			pw_merge_from_pivot(t_ab *ab, int pivot)
{
	int			*a_top;
	int			*b_top;
	int			i;
	int			rotations;

	rotations = 0;
	i = ab->b.count;
	while (i--)
	{
		a_top = a_get(&ab->a, 0);
		b_top = a_get(&ab->b, 0);
		if (*b_top > pivot)
		{
			while (*a_top < *b_top)
			{
				ra(ab);
				rotations++;
				a_top = a_get(&ab->a, 0);
			}
			pa(ab);
			while (rotations)
			{
				rra(ab);
				rotations--;
			}
		}
		else
			rb(ab);
	}
}
/*
**	---------------------------------------------------------------------------
**
**	Reassemble the values from stack b to stack a.
**
*/
void			pw_reassemble(t_ab *ab)
{
	int			*b_top;
	int			*b_second;
	size_t		pivot;

	pivot = pw_get_pivot(&ab->b);
	pw_merge_from_pivot(ab, pivot);
	if (ab->b.count > 3)
		pw_reassemble(ab);
	if (ab->b.count == 3)
		pw_sort_last3_in_b(ab);
	else if (ab->b.count == 2)
	{
		b_top = a_get(&ab->b, 0);
		b_second = a_get(&ab->b, 1);
		if (*b_top < *b_second)
			sb(ab);
	}
	while (ab->b.count)
		pa(ab);
}
/*
**	---------------------------------------------------------------------------
**
**	Disassemble the values from stack a into stack b by splitting from below
**	the pivot ie. the median of stack a into stack b. When only 3 values
**	remain, they are sorted in place.
**
*/
void			pw_disassemble(t_ab *ab)
{
	int			*a_top;
	int			*a_second;
	int			pivot;

	if (ab->a.count <= 3)
	{
		if (ab->a.count == 3)
			pw_sort_last3_in_a(ab);
		else if (ab->b.count == 2)
		{
			a_top = a_get(&ab->a, 0);
			a_second = a_get(&ab->a, 1);
			if (*a_top > *a_second)
				sb(ab);
		}
		pw_reassemble(ab);
		return ;
	}
	pivot = pw_get_pivot(&ab->a);
	a_top = a_get(&ab->a, 0);
	a_second = a_get(&ab->a, 1);
	pw_split_from_pivot(ab, pivot);
	pw_disassemble(ab);
}

t_arr			pw_remove_extra_rotations(t_arr *commands)
{
	t_arr		out;
	size_t		i;
	int			rotations;

	out = a_alloc(commands->count);
	rotations = 0;
	i = 0;
	while (i < commands->count)
	{
		while (s_cmp(a_get(commands, i), "rra") == 0)	
		{
			rotations++;
			i++;
		}
		while (rotations > 0 && s_cmp(a_get(commands, i), "ra") == 0)	
		{
			rotations--;
			i++;
		}
		while (rotations > 0)
		{
			a_add(&out, "rra");
			rotations--;
		}
		a_add(&out, a_get(commands, i));
		i++;
	}
	return (out);
}

int				main(int argc, char **argv)
{
	t_ab		ab;
	t_arr		args;

	if (argc < 0)
		return (0);
	args = a_alloc(100);
	a_readfile(&args, argv[1]);
	ab = pw_prepaper_ab(args.count, (char **)args.data);
	pw_disassemble(&ab);
	t_arr commands = pw_remove_extra_rotations(&ab.commands);
	a_iter(&commands, pw_print_str);
}

