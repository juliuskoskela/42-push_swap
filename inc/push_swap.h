#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "../core/inc/core.h"

typedef struct	s_stacks
{
	t_array		a;
	t_array		b;
	t_parray	commands;
	size_t		stack_size;
}				t_stacks;

static const t_size	cmd_count = 11;

static const char	*comid [] =
{
	"sa",
	"sb",
	"ss",
	"pa",
	"pb",
	"ra",
	"rb",
	"rr",
	"rra",
	"rrb",
	"rrr"
};

typedef enum	e_flags
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
}				t_flags;

void			sa(t_stacks *ab);
void			sb(t_stacks *ab);
void			ss(t_stacks *ab);
void			pa(t_stacks *ab);
void			pb(t_stacks *ab);
void			ra(t_stacks *ab);
void			rb(t_stacks *ab);
void			rr(t_stacks *ab);
void			rra(t_stacks *ab);
void			rrb(t_stacks *ab);
void			rrr(t_stacks *ab);

typedef void (*t_command)(t_stacks *ab);

static const	t_command g_cmd[] =
{
	sa,
	sb,
	ss,
	pa,
	pb,
	ra,
	rb,
	rr,
	rra,
	rrb,
	rrr
};


void			pw_sort_a(t_stacks *ab, size_t a_part);
void			pw_sort_b(t_stacks *ab, size_t b_part);
size_t			pw_split_from_pivot_a(t_stacks *ab, int pivot, size_t part_size);
size_t			pw_split_from_pivot_b(t_stacks *ab, int pivot, size_t part_size);
void			pw_sort3a(t_stacks *ab);
void			pw_sort3b(t_stacks *ab);
void			pw_sort3a_simple(t_stacks *ab);
void			pw_sort3b_simple(t_stacks *ab);

t_array			pw_norm_arr(t_array arr);
t_stacks		pw_prepaper_ab(int argc, char **argv);
t_stacks		pw_new_ab(size_t size);
int				pw_cmp(void *a, void *b);
int				pw_check(t_array a);
void			pw_print_stacks(t_stacks ab);
int				pw_find_pos(t_array a, int *item);
size_t			pw_sum(t_array *arr, size_t count);
void			pw_print_stacks(t_stacks ab);
void			pw_print_str(void **data, size_t i);
void			pw_print_int(void **data, size_t i);

#endif
