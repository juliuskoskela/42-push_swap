# include "../inc/push_swap.h"

static t_ssize	print_str(void *data, t_size i)
{
	char	*str;

	str = data;
	print("%s\n", str);
	return (i);
}

int	main(int argc, char **argv)
{
	t_stacks	ab;

	if (argc < 2)
		return (-1);
	ab = ps_new_stack(argv[1]);
	ps_sort(&ab);
	parr_iter(&ab.commands, print_str);
	//print("\n");
	if (ps_sorted(ab.a) == FALSE || ab.b.len > 0)
		print("Sorting failed!\n");
	//ps_print_stacks(ab);
	ps_free_stacks(ab);
}
