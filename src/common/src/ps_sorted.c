#include "../inc/common.h"

t_bool	ps_sorted(t_array src)
{
	t_size	i;
	int		*f;
	int		*s;

	i = 1;
	while (i < src.len)
	{
		f = arr_get(&src, i - 1);
		s = arr_get(&src, i);
		if (*s <= *f)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
