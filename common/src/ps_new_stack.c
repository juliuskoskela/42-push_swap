#include "../inc/common.h"

static int	is_legal(char c)
{
	if (!is_digit(c) && c != ' ')
		return (0);
	return (1);
}

static int	ps_find_position(t_array a, int n)
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

static t_array	ps_norm_stack(t_array raw)
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

static int ps_parse_args(t_array *raw, char *args)
{
	int		nbr;
	t_size	i;

	i = 0;
	while (args[i] != '\0')
	{
		if (!is_legal(args[i]))
			return (-1);
		if (is_digit(args[i]))
		{
			nbr = s_toi(&args[i]);
			arr_add_last(raw, &nbr);
			while (is_digit(args[i]))
				i++;
		}
		else
			i++;
	}
	return (1);
}

t_stacks	ps_new_stack(char *args)
{
	t_stacks	ab;
	t_array		raw;

	raw = arr_new(1, sizeof(int));
	if (ps_parse_args(&raw, args) == -1)
	{
		print("Error while reading arguments!\n");
		exit(-1);
	}
	ab.a = ps_norm_stack(raw);
	arr_free(&raw);
	ab.b = arr_new(1, sizeof(int));
	ab.commands = parr_new(1);
	ab.stack_size = ab.a.len;
	return (ab);
}
