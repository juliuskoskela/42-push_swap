#include "../inc/common.h"

static int	is_legal(char c)
{
	if (!is_digit(c) && c != ' ')
		return (0);
	return (1);
}

static void	ps_check_duplicate(t_array *raw, int nbr)
{
	int		*ptr;
	t_size	i;

	i = 0;
	while (i < raw->len)
	{
		ptr = arr_get(raw, i);
		if (*ptr == nbr)
		{
			print("Error\n");
			exit(-1);
		}
		i++;
	}
}

static int ps_parse_args(t_array *raw, char *args)
{
	t_int64	nbr;
	t_size	i;

	i = 0;
	while (args[i] != '\0')
	{
		if (!is_legal(args[i]))
			return (-1);
		if (is_digit(args[i]))
		{
			nbr = s_toi(&args[i]);
			if (nbr > 2147483627 || nbr < 0)
			{
				print("Error\n");
				exit(-1);
			}
			ps_check_duplicate(raw, nbr);
			arr_add_last(raw, &nbr);
			while (is_digit(args[i]))
				i++;
		}
		else
			i++;
	}
	return (1);
}

t_stacks	ps_new_stack(int argc, char **argv)
{
	t_stacks	ab;
	t_array		raw;
	int			i;

	raw = arr_new(1, sizeof(int));
	i = 1;
	while (i < argc)
	{
		if (ps_parse_args(&raw, argv[i]) == -1)
		{
			print("Error\n");
			exit(-1);
		}
		i++;
	}
	ab.a = ps_norm_stack(raw);
	arr_free(&raw);
	ab.b = arr_new(1, sizeof(int));
	ab.commands = parr_new(1);
	ab.stack_size = ab.a.len;
	return (ab);
}
