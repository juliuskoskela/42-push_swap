#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "../../core/inc/core.h"
# include "../common/inc/common.h"

typedef struct s_rots
{
	int			a;
	int			b;
}				t_rots;

///////////////////////////////////////////////////////////////////////////////

int			main(int argc, char **argv);
int			ps_calc_dist(t_stacks *ab, t_size src_index);
void		ps_exec_moves(t_stacks *ab, t_rots rots);
int			ps_value_target_index(t_stacks *ab, int b_val);
t_rots		ps_calc_opt_rots(t_stacks *ab, int src_index);
t_rots		ps_merge_rots(t_rots rots);
int			ps_stack_zero_index(t_stacks *ab);
void		ps_merge(t_stacks *ab);
void		ps_sort(t_stacks *ab);
void		ps_rot_sorted_substack(t_stacks *ab);

#endif
