#include "../inc/push_swap.h"






































// 1 2 5 3 4 0


int			pw_sort6_simple(t_ab *ab)
{
	return (0);	
}

int			main(void)
{
	t_ab	ab;
	int		numbers[6][1] = {{1}, {2}, {5}, {3}, {4}, {0}};
	ab = pw_new_ab(6);
	a_assign(&ab.a, (void **)numbers, 6);
	pw_sort6_simple(&ab);
	pw_sort6_simple(&ab);
	pw_print_stacks(ab);
}
