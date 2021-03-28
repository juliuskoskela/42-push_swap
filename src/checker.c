#include "../inc/push_swap.h"






































int				main(int argc, char **argv)
{
	t_ab	ab;
	t_arr	args;

	args = a_alloc(100);
	a_readfile(&args, argv[1]);
	ab = pw_prepaper_ab(args.count, (char **)args.data);
	print_stacks(ab);
	printf("\nsorted: %d", check(ab.a));
}

