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

int	ps_check_cmd(char *cmd)
{
	char	*cmd_id [] = { "sa", "sb", "ss",
							"pa", "pb", "ra",
							"rb", "rr", "rra",
							"rrb", "rrr" };
	t_size	i;

	i = 0;
	while (i < 11)
	{
		if (s_cmp(cmd, cmd_id[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	exit_usage(void)
{
	print("usage: [args]\n");
	exit(-1);
}

int	main(int argc, char **argv)
{
	char		*cur_cmd;
	int			cmd_flag;
	t_stacks	ab;

	if (argc != 2)
		exit_usage();
	ab = ps_new_stack(argv[1]);
	while (ps_get_cmd(&cur_cmd) > 0)
	{
		cmd_flag = ps_check_cmd(cur_cmd);
		if (cmd_flag == -1)
		{
			print("Invalid command!\n");
			exit(-1);
		}
		ps_exec(&ab, 1, cmd_flag);
		free(cur_cmd);
	}
	if (ps_sorted(ab.a) && ab.b.len == 0)
		print("OK\n");
	else
		print("KO\n");
	ps_free_stacks(ab);
}
