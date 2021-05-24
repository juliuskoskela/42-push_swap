# include "../inc/push_swap.h"
# include <string.h>
# define PRINT print

///////////////////////////////////////////////////////////////////////////////

t_ssize		print_uint64(void *data, t_size i);
void		pw_print_stacks(t_stacks ab);
int			pw_conv_command(char *cmd);
t_ssize		pw_print_nbr(void *data, t_size i);
int			pw_find_position(t_array a, int n);
t_array		pw_parse_stack(t_page input);
t_array		pw_norm_stack(t_array raw);
t_ssize		free_str(void *data, t_size i);
t_stacks	pw_new_stack(char *filename);
void		pw_free_stacks(t_stacks ab);
t_bool		pw_sorted(t_array src);

///////////////////////////////////////////////////////////////////////////////

static int	check_case(t_array *arr);
void		pw_sort_last3_in_b(t_stacks *ab);
void		pw_sort_last3_in_a(t_stacks *ab);
t_size		pw_get_pivot(t_array *arr);
void		pw_split_from_pivot(t_stacks *ab, int pivot);
void		pw_merge_from_pivot(t_stacks *ab, int pivot);
void		pw_reassemble(t_stacks *ab);
void		pw_disassemble(t_stacks *ab);

///////////////////////////////////////////////////////////////////////////////

t_bool		pw_sorted(t_array src)
{
	t_size	i;
	int		*f;
	int		*s;

	i = 1;
	while (i < src.len)
	{
		f = arr_get(&src, i - 1);
		s = arr_get(&src, i);
		if (*s <= *f)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int main(int argc, char **argv)
{
	t_stacks	ab;

	ab = pw_new_stack(argv[1]);
	pw_print_stacks(ab);
	pw_disassemble(&ab);
	pw_print_stacks(ab);
	if (pw_sorted(ab.a))
		print("sorted = yes\n");
	else
		print("sorted = no\n");
	pw_free_stacks(ab);
}

///////////////////////////////////////////////////////////////////////////////

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

void	pw_sort_last3_in_b(t_stacks *ab)
{
	int	case3;

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

void	pw_sort_last3_in_a(t_stacks *ab)
{
	int	case3;

	// PRINT("sort 3 a\n");
	// arr_iter(&ab->a, pw_print_nbr);
	case3 = check_case(&ab->a);
	// PRINT("case = %d\n", case3);
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

t_size	pw_get_pivot(t_array *arr)
{
	t_size	i;
	t_size	res;
	int		*ptr;

	i = 0;
	res = 0;
	while (i < arr->len)
	{
		ptr = arr_get(arr, i);
		res += *ptr;
		i++;
	}
	return (res / arr->len);
}

void	pw_split_from_pivot(t_stacks *ab, int pivot)
{
	int	*top;
	int	i;

	// PRINT("split form pivot\n");
	// arr_iter(&ab->a, pw_print_nbr);
	// PRINT("\n");
	i = ab->a.len;
	while (i--)
	{
		top = arr_get(&ab->a, 0);
		// print("%d\n", *top);
		if (*top < pivot)
			pb(ab);
		else
			ra(ab);
	}
	// PRINT("split form pivot\n");
	// arr_iter(&ab->a, pw_print_nbr);
	// PRINT("\n");
}

void	pw_merge_from_pivot(t_stacks *ab, int pivot)
{
	int	*a_top;
	int	*b_top;
	int	i;
	int	rotations;

	rotations = 0;
	i = ab->b.len;
	// PRINT("merge form pivot\n");
	// arr_iter(&ab->a, pw_print_nbr);
	// PRINT("\n");
	// arr_iter(&ab->b, pw_print_nbr);
	// PRINT("\n");
	while (i--)
	{
		a_top = arr_get(&ab->a, 0);
		b_top = arr_get(&ab->b, 0);
		// print("%d\n", *a_top);
		// print("%d\n", *b_top);
		if (*b_top > pivot)
		{
			while (*a_top < *b_top)
			{
				ra(ab);
				rotations++;
				a_top = arr_get(&ab->a, 0);
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

void	pw_reassemble(t_stacks *ab)
{
	int		*b_top;
	int		*b_second;
	t_size	pivot;

	pivot = pw_get_pivot(&ab->b);
	pw_merge_from_pivot(ab, pivot);
	if (ab->b.len > 3)
		pw_reassemble(ab);
	if (ab->b.len == 3)
		pw_sort_last3_in_b(ab);
	else if (ab->b.len == 2)
	{
		b_top = arr_get(&ab->b, 0);
		b_second = arr_get(&ab->b, 1);
		if (*b_top < *b_second)
			sb(ab);
	}
	while (ab->b.len)
		pa(ab);
}

void	pw_disassemble(t_stacks *ab)
{
	int	*a_top;
	int	*a_second;
	int	pivot;

	if (ab->a.len <= 3)
	{
		if (ab->a.len == 3)
			pw_sort_last3_in_a(ab);
		else if (ab->a.len == 2)
		{
			a_top = arr_get(&ab->a, 0);
			a_second = arr_get(&ab->a, 1);
			if (*a_top > *a_second)
				sb(ab);
		}
		pw_reassemble(ab);
		return ;
	}
	pivot = pw_get_pivot(&ab->a);
	pw_split_from_pivot(ab, pivot);
	pw_disassemble(ab);
}

///////////////////////////////////////////////////////////////////////////////

t_ssize	print_int(void *data, t_size i)
{
	int	*ptr;

	ptr = data;
	print("%d ", *ptr);
	return (i);
}

void	pw_print_stacks(t_stacks ab)
{
	print("a: ");
	arr_iter(&ab.a, print_int);
	print("\nb: ");
	arr_iter(&ab.b, print_int);
	print("\n");
	print("commands count = %d\n", ab.commands.len);
}

int	pw_conv_command(char *cmd)
{
	t_size	i;

	i = 0;
	while (i < cmd_count)
	{
		if (s_cmp(comid[i], cmd) == 0)
			return (i);
	}
	return (-1);
}

t_ssize	pw_print_nbr(void *data, t_size i)
{
	int	*num;

	if (data == NULL)
		return (-1);
	num = data;
	print("[%llu] %d \n", i, *num);
	return (i);
}

int	pw_find_position(t_array a, int n)
{
	int	*numptr;
	t_size		pos;
	t_size		i;

	i = 0;
	pos = 0;
	while (i < a.len)
	{
		numptr = arr_get(&a, i);
		if (*numptr < n)
			pos++;
		i++;
	}
	return (pos);
}

t_array	pw_parse_stack(t_page input)
{
	t_array	out;
	int		cur;
	t_size	i;

	out = arr_new(1, sizeof(int));
	i = 0;
	while (i < input.len)
	{
		cur = str_toi(page_get(&input, i));
		arr_add_last(&out, &cur);
		i++;
	}
	return (out);
}

t_array	pw_norm_stack(t_array raw)
{
	t_array	out;
	int		*n;
	int		pos;
	t_size	i;

	out = arr_new(1, sizeof(int));
	i = 0;
	while (i < raw.len)
	{
		n = arr_get(&raw, i);
		pos = pw_find_position(raw, *n);
		arr_add_last(&out, &pos);
		i++;
	}
	return (out);
}

t_ssize		free_str(void *data, t_size i)
{
	t_str	*ptr;

	ptr = data;
	str_free(ptr);
	return (i);
}

t_stacks	pw_new_stack(char *filename)
{
	t_page		file;
	t_stacks	ab;
	t_array		raw;

	file = page_new(1);
	page_read_file(&file, filename);
	raw = pw_parse_stack(file);
	arr_iter(&raw, print_int);
	print("\n");
	arr_iter(&file, free_str);
	arr_free(&file);
	ab.a = pw_norm_stack(raw);
	arr_free(&raw);
	ab.b = arr_new(1, sizeof(int));
	ab.commands = arr_new(1, sizeof(int));
	ab.stack_size = ab.a.len;
	return (ab);
}

void	pw_free_stacks(t_stacks ab)
{
	arr_free(&ab.a);
	arr_free(&ab.b);
	arr_free(&ab.commands);
}
