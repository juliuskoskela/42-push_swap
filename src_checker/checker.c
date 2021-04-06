#include "../inc/push_swap.h"

void			pw_execute_commands(t_ab *ab, t_arr *commands)
{
	size_t		i;

	i = 0;
	while (i < commands->count)
	{
		if (s_cmp(a_get(commands, i), "ra") == 0)
			ra(ab);
		else if (s_cmp(a_get(commands, i), "rra") == 0)
			rra(ab);
		else if (s_cmp(a_get(commands, i), "rb") == 0)
			rb(ab);
		else if (s_cmp(a_get(commands, i), "rrb") == 0)
			rrb(ab);
		else if (s_cmp(a_get(commands, i), "rrr") == 0)
			rrr(ab);
		else if (s_cmp(a_get(commands, i), "pa") == 0)
			pa(ab);
		else if (s_cmp(a_get(commands, i), "pb") == 0)
			pb(ab);
		else if (s_cmp(a_get(commands, i), "sa") == 0)
			sa(ab);
		else if (s_cmp(a_get(commands, i), "sb") == 0)
			sb(ab);
		else if (s_cmp(a_get(commands, i), "ss") == 0)
			ss(ab);
		i++;
	}
}

int				main(int argc, char **argv)
{
	t_ab	ab;
	t_arr	args;
	t_arr	commands;
	
	if (argc < 0)
		return (0);
	args = a_alloc(100);
	commands = a_alloc(100);
	a_readfile(&args, argv[1]);
	a_readfile(&commands, argv[2]);
	ab = pw_prepaper_ab(args.count, (char **)args.data);
	pw_execute_commands(&ab, &commands);
	a_iter(&ab.a, pw_print_int);
	if (pw_check(ab.a) == 1)
		printf("\nStack sorted successfully using %zu commands", commands.count - 1);
	else
		printf("Sorting unsuccessful.\n");
	a_dalloc(&args);
}

