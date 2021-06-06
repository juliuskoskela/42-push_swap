#include "../inc/checker.h"

static int	ps_get_cmd(char **dst)
{
	char	buf[5];
	int		ret;
	int		i;

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
		return (-1);
	}
	buf[i] = '\0';
	*dst = s_dup(buf);
	if (*dst == NULL)
		return (-1);
	return (1);
}

static int	ps_check_cmd(char *cmd)
{
	char	*cmd_id [] = {
		"sa", "sb", "ss",
		"pa", "pb", "ra",
		"rb", "rr", "rra",
		"rrb", "rrr", "done"};
	t_size	i;

	i = 0;
	while (i < 12)
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
		if (cmd_flag == DONE)
			break ;
		if (cmd_flag == -1
			|| (cmd_flag == PA && ab->b.len == 0)
			|| (cmd_flag == PB && ab->a.len == 0))
			print("Error\n");
		else if (cmd_flag >= 0 && cmd_flag < 11)
			ps_exec(ab, 1, cmd_flag);
		else
			print("Error\n");
		if (verb == 1)
			ps_print_stacks(*ab);
		free(cur_cmd);
	}
}

int	main(int argc, char **argv)
{
	int			verb;
	t_stacks	ab;

	verb = 0;
	if (argc < 2)
		exit(-1);
	if (s_cmp(argv[1], "-v") == 0)
		verb = 1;
	ab = ps_new_stack(argc - verb, argv + verb);
	ps_cmd_loop(&ab, verb);
	if (ps_sorted(ab.a) && ab.b.len == 0)
		print("OK\n");
	else
		print("KO\n");
	if (verb == 1)
		print("COMMANDS USED %d\n", ab.commands.len);
	ps_free_stacks(ab);
}
