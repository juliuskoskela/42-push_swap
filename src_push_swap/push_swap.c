# include "../inc/push_swap.h"
# include <string.h>
# define PRINT print

typedef struct	s_rotab
{
	int			a;
	int			b;
}				t_rotab;

t_ssize	print_int(void *data, t_size i);

///////////////////////////////////////////////////////////////////////////////

t_ssize		print_uint64(void *data, t_size i);
void		ps_print_stacks(t_stacks ab);
int			ps_conv_command(char *cmd);
t_ssize		ps_print_nbr(void *data, t_size i);
int			ps_find_position(t_array a, int n);
t_array		ps_parse_stack(t_page input);
t_array		ps_norm_stack(t_array raw);
t_ssize		free_str(void *data, t_size i);
t_stacks	ps_new_stack(char *filename);
void		ps_free_stacks(t_stacks ab);
t_bool		ps_sorted(t_array src);

///////////////////////////////////////////////////////////////////////////////

static int	check_case(t_array *arr);
void		ps_sort_last3_in_b(t_stacks *ab);
void		ps_sort_last3_in_a(t_stacks *ab);
t_size		ps_get_pivot(t_array *arr);
void		ps_split_from_pivot(t_stacks *ab, int pivot);
void		ps_merge_from_pivot(t_stacks *ab, int pivot);
void		ps_reassemble(t_stacks *ab);
void		ps_disassemble(t_stacks *ab);

///////////////////////////////////////////////////////////////////////////////

int	ps_get_zero_index(t_stacks *ab)
{
	int		*val_1;
	int		*val_2;
	t_size	i;

	i = ab->a.len - 1;
	while (i > 0)
	{
		val_1 = arr_get(&ab->a, i);
		val_2 = arr_get(&ab->a, i - 1);
		if (*val_1 < *val_2)
			return (i);
		i--;
	}
	return (0);
}

int	ps_pos_in_a(t_stacks *ab, int b_val)
{
	int		*a_val;
	t_size	zero_pos;
	t_size	i;

	zero_pos = ps_get_zero_index(ab);
	i = zero_pos;
	while (1)
	{
		a_val = arr_get(&ab->a, i);
		if (*a_val > b_val)
			return (i);
		i = (i + 1) % ab->a.len;
		if (i == zero_pos)
			break ;
	}
	return (zero_pos);
}

t_rotab	ps_opt_rots(t_stacks *ab, t_rotab rots)
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

t_rotab	ps_calc_rots(t_stacks *ab, int src_index)
{
	t_rotab	rots;
	int		*b_val;
	int		dst_index;

	b_val = arr_get(&ab->b, src_index);
	dst_index = ps_pos_in_a(ab, *b_val);
	if (src_index >= ab->b.len / 2)
		rots.b = ab->b.len - src_index;
	else
		rots.b = -src_index;
	if (dst_index >= ab->a.len / 2)
		rots.a = ab->a.len - dst_index;
	else
		rots.a = -dst_index;
	return (rots);
}

int		ps_calc_dist(t_stacks *ab, t_size src_index)
{
	t_rotab	rots;

	rots = ps_calc_rots(ab, src_index);
	if ((rots.a > 0 && rots.b > 0)
		|| (rots.a < 0 && rots.b < 0))
		rots = ps_opt_rots(ab, rots);
	return (math_abs(rots.a) + math_abs(rots.b) + 1);
}

t_size	ps_choose_val_in_b(t_stacks *ab)
{
	int		tmp;
	int		ret;
	t_size	pos;
	t_size	i;

	ret = ps_calc_dist(ab, 0);
	pos = 0;
	i = 1;
	while (i < ab->b.len)
	{
		tmp = ps_calc_dist(ab, i);
		if (tmp < ret)
		{
			ret = tmp;
			pos = i;
		}
		i++;
	}
	return (pos);
}

void	ps_exec(t_stacks *ab, t_size count, int cmd)
{
	t_size	i;

	i = 0;
	while (i < count)
	{
		g_cmd[cmd](ab);
		i++;
	}
}

t_rotab	ps_merge_rots(t_stacks *ab, t_rotab rots)
{
	if (rots.a > 0)
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
	}
	else
	{
		if (rots.a < rots.b)
		{
			ps_exec(ab, math_abs(rots.b), RR);
			rots.a -= rots.b;
			rots.b = 0;
		}
		else
		{
			ps_exec(ab, math_abs(rots.a), RR);
			rots.b -= rots.a;
			rots.a = 0;
		}
	}
	return (rots);
}

void	ps_exec_moves(t_stacks *ab, t_rotab rots)
{

	if ((rots.a > 0 && rots.b > 0)
		|| (rots.a < 0 && rots.b < 0))
		rots = ps_merge_rots(ab, rots);
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

void	ps_rot_back(t_stacks *ab)
{
	int		index;

	index = ps_get_zero_index(ab);
	if (index >= ab->a.len / 2)
		ps_exec(ab, ab->a.len - index, RRA);
	else
		ps_exec(ab, index, RA);
}

void	ps_opt_extra(t_stacks *ab)
{
	int	*a_top;
	int	*a_sec;
	int	*b_top;
	int	*b_sec;

	a_top = arr_get(&ab->a, 0);
	a_sec = arr_get(&ab->a, 1);
	b_top = arr_get(&ab->b, 0);
	b_sec = arr_get(&ab->b, 1);
	if (*a_top > *a_sec && *b_top < *b_sec)
		ss(ab);
	else if (*a_top > *a_sec)
		sa(ab);
	else if (*b_top < *b_sec)
		sb(ab);
}

int	ps_merge(t_stacks *ab)
{
	t_rotab	rots;
	t_size	src_index;
	t_size	i;

	i = 0;
	while (ab->b.len)
	{
		if (ab->a.len > 2 && ab->b.len > 2
			&& ab->stack_size > 100)
			ps_opt_extra(ab);
		src_index = ps_choose_val_in_b(ab);
		rots = ps_calc_rots(ab, src_index);
		ps_exec_moves(ab, rots);
	}
	ps_rot_back(ab);
	return (1);
}

int	ps_calc_sorted(t_stacks *ab)
{
	int	*bot;
	int	*sec;
	t_size	i;
	t_size	j;

	j = 0;
	i = ab->a.len - 1;
	while (i > 1)
	{
		bot = arr_get(&ab->a, i);
		sec = arr_get(&ab->a, i - 1);
		if (*bot > *sec)
			break ;
		i--;
		j++;
	}
	return (j);
}

void	ps_rot_sorted(t_stacks *ab)
{
	int	*top;
	int	*bot;

	while (1)
	{
		top = arr_get_first(&ab->a);
		bot = arr_get_last(&ab->a);
		if (*top < *bot)
			break ;
		rra(ab);
	}
}

void	ps_split(t_stacks *ab, int len)
{
	int *a_top;
	int *a_bot;
	int *b_top;
	int *b_bot;
	int	rem;
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
	// ps_print_stacks(*ab);
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

t_ssize	print_str(void *data, t_size i)
{
	char	*str;

	str = data;
	print("%s\n", str);
	return (i);
}

int main(int argc, char **argv)
{
	t_stacks	ab;

	ab = ps_new_stack(argv[1]);
	ps_sort(&ab);
	if (ps_sorted(ab.a) == FALSE || ab.b.len > 0)
		print("Sorting failed!\n");
	parr_iter(&ab.commands, print_str);
	// print("count = %d\n", ab.commands.len);
	ps_free_stacks(ab);
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

void	ps_sort_last3_in_b(t_stacks *ab)
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

void	ps_sort_last3_in_a(t_stacks *ab)
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

///////////////////////////////////////////////////////////////////////////////


t_bool		ps_sorted(t_array src)
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

t_ssize	print_int(void *data, t_size i)
{
	int	*ptr;

	ptr = data;
	print("%d ", *ptr);
	return (i);
}

void	ps_print_stacks(t_stacks ab)
{
	print("a: ");
	arr_iter(&ab.a, print_int);
	print("\nb: ");
	arr_iter(&ab.b, print_int);
	print("\n");
	print("commands count = %d\n", ab.commands.len);
}

int	ps_conv_command(char *cmd)
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

t_ssize	ps_print_nbr(void *data, t_size i)
{
	int	*num;

	if (data == NULL)
		return (-1);
	num = data;
	print("[%llu] %d \n", i, *num);
	return (i);
}

int	ps_find_position(t_array a, int n)
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

t_array	ps_parse_stack(t_page input)
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

t_array	ps_norm_stack(t_array raw)
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
		pos = ps_find_position(raw, *n);
		arr_add_last(&out, &pos);
		i++;
	}
	return (out);
}

t_ssize	free_str(void *data, t_size i)
{
	t_str	*ptr;

	ptr = data;
	str_free(ptr);
	return (i);
}

t_stacks	ps_new_stack(char *filename)
{
	t_page		file;
	t_stacks	ab;
	t_array		raw;

	file = page_new(1);
	page_read_file(&file, filename);
	raw = ps_parse_stack(file);
	arr_iter(&file, free_str);
	arr_free(&file);
	ab.a = ps_norm_stack(raw);
	arr_free(&raw);
	ab.b = arr_new(1, sizeof(int));
	ab.commands = parr_new(1);
	ab.stack_size = ab.a.len;
	return (ab);
}

void	ps_free_stacks(t_stacks ab)
{
	arr_free(&ab.a);
	arr_free(&ab.b);
	parr_free(&ab.commands);
}
