#ifndef COMMON_H
# define COMMON_H
# include "../../core/inc/core.h"

typedef struct	s_stacks
{
	t_array		a;
	t_array		b;
	t_parray	commands;
	size_t		stack_size;
}				t_stacks;

typedef enum	e_flags
{
	SA, SB, SS, PA, PB, RA,
	RB, RR, RRA, RRB, RRR, DONE
}				t_flags;

void	sa(t_stacks *ab);
void	sb(t_stacks *ab);
void	ss(t_stacks *ab);
void	pa(t_stacks *ab);
void	pb(t_stacks *ab);
void	ra(t_stacks *ab);
void	rb(t_stacks *ab);
void	rr(t_stacks *ab);
void	rra(t_stacks *ab);
void	rrb(t_stacks *ab);
void	rrr(t_stacks *ab);

typedef void (*t_command)(t_stacks *ab);

static const	t_command g_cmd[] =
{
	sa, sb, ss, pa, pb, ra,
	rb, rr, rra, rrb, rrr
};

void		ps_exec(t_stacks *ab, t_size count, int cmd);
void		ps_free_stacks(t_stacks ab);
t_stacks	ps_new_stack(int argc, char **argv);
void		ps_print_stacks(t_stacks ab);
t_bool		ps_sorted(t_array src);
t_array		ps_norm_stack(t_array raw);

#endif
