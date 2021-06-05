#include "../inc/common.h"

static t_ssize	print_int(void *data, t_size i)
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
