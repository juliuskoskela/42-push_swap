#include "../inc/common.h"

void	ps_exec(t_stacks *ab, t_size count, int cmd)
{
	t_size	i;

	i = 0;
	while (i < count)
	{
		g_cmd[cmd](ab);
		i++;
	}
}
