#include "../inc/checker.h"

static int	ps_get_cmd(char **dst)
{
	char	buf[5];
	int		ret;
	int		i;

	mzero(buf, sizeof(char) * 5);
	i = 0;
	while (i < 4)
	{
		ret = read(0, &buf[i], 1);
		if ((ret == 0 && i == 0) || ret == -1)
			return (ret);
		if (buf[i] == '\n')
			break ;
		i++;
	}
	if (buf[i] != '\n')
	{
		s_readline(0, dst);
		print("Error\n");
		exit(-1);
	}
	buf[i] = '\0';
	*dst = s_dup(buf);
	return (1);
}

static int	ps_check_cmd(char *cmd)
{
	static char	*cmd_id [] = {
		"sa", "sb", "ss",
		"pa", "pb", "ra",
		"rb", "rr", "rra",
		"rrb", "rrr"};
	t_size		i;

	i = 0;
	while (i < 11)
	{
		if (s_cmp(cmd, cmd_id[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void	ps_cmd_loop(t_stacks *ab, int verb)
{
	char		*cur_cmd;
	int			cmd_flag;

	while (ps_get_cmd(&cur_cmd) > 0)
	{
		cmd_flag = ps_check_cmd(cur_cmd);
		if ((cmd_flag == PA && ab->b.len == 0)
			|| (cmd_flag == PB && ab->a.len == 0))
			print("");
		else if (cmd_flag >= 0 && cmd_flag < 11)
			ps_exec(ab, 1, cmd_flag);
		else if (cmd_flag == -1)
		{
			print("Error\n");
			exit(-1);
		}
		if (verb == 1)
			ps_print_stacks(*ab);
		free(cur_cmd);
	}
}

static void	ps_calc_commands(t_parray cmds)
{
	int		cc[11];
	char	*cur;
	t_size	i;

	mzero(&cc[0], sizeof(int) * 11);
	i = 0;
	while (i < cmds.len)
	{
		cur = parr_get(&cmds, i);
		cc[ps_check_cmd(cur)] += 1;
		i++;
	}
	print("sa = %3.1f %%\n", 100 * ((double) cc[SA] / (double)cmds.len));
	print("sb = %3.1f %%\n", 100 * ((double) cc[SB] / (double)cmds.len));
	print("ss = %3.1f %%\n", 100 * ((double) cc[SS] / (double)cmds.len));
	print("pa = %3.1f %%\n", 100 * ((double) cc[PA] / (double)cmds.len));
	print("pb = %3.1f %%\n", 100 * ((double) cc[PB] / (double)cmds.len));
	print("ra = %3.1f %%\n", 100 * ((double) cc[RA] / (double)cmds.len));
	print("rb = %3.1f %%\n", 100 * ((double) cc[RB] / (double)cmds.len));
	print("rr = %3.1f %%\n", 100 * ((double) cc[RR] / (double)cmds.len));
	print("rra = %3.1f %%\n", 100 * ((double) cc[RRA] / (double)cmds.len));
	print("rrb = %3.1f %%\n", 100 * ((double) cc[RRB] / (double)cmds.len));
	print("rrr = %3.1f %%\n", 100 * ((double) cc[RRR] / (double)cmds.len));
}

int	main(int argc, char **argv)
{
	int			verb;
	t_stacks	ab;

	verb = 0;
	if (argc < 2 || (argc == 2 && s_cmp(argv[1], "-v") == 0))
		exit(-1);
	if (s_cmp(argv[1], "-v") == 0)
		verb = 1;
	ab = ps_new_stack(argc - verb, argv + verb);
	if (verb == 1)
		ps_print_stacks(ab);
	ps_cmd_loop(&ab, verb);
	if (ps_sorted(ab.a) && ab.b.len == 0)
		print("OK\n");
	else
		print("KO\n");
	if (verb == 1)
	{
		print("COMMANDS USED %d\n", ab.commands.len);
		ps_calc_commands(ab.commands);
	}
	ps_free_stacks(ab);
}
