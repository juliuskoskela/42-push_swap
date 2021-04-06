#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "../array/inc/array.h"
# include "../string/inc/string.h"
# include <time.h>
#include <stdio.h>
#include <stdlib.h>
# define LARGER 1
# define SMALLER -1

typedef struct	s_ab
{
	t_arr		a;
	t_arr		b;
	t_arr		commands;
	t_arr		partitions;
	size_t		stack_size;
}				t_ab;

void			pw_sort_a(t_ab *ab, size_t a_part);
void			pw_sort_b(t_ab *ab, size_t b_part);
size_t			pw_split_from_pivot_a(t_ab *ab, int pivot, size_t part_size);
size_t			pw_split_from_pivot_b(t_ab *ab, int pivot, size_t part_size);
void			pw_sort3a(t_ab *ab);
void			pw_sort3b(t_ab *ab);
void            pw_sort3a_simple(t_ab *ab);
void            pw_sort3b_simple(t_ab *ab);

t_arr			pw_norm_arr(t_arr arr);
t_ab			pw_prepaper_ab(int argc, char **argv);
t_ab			pw_new_ab(size_t size);
int				pw_cmp(void *a, void *b);
int				pw_check(t_arr a);
void			pw_print_stacks(t_ab ab);
int				pw_find_pos(t_arr a, int *item);
size_t			pw_sum(t_arr *arr, size_t count);
void			pw_print_stacks(t_ab ab);
void			pw_print_str(void **data, size_t i);
void			pw_print_int(void **data, size_t i);

void			sa(t_ab *ab);
void			sb(t_ab *ab);
void			ss(t_ab *ab);
void			pa(t_ab *ab);
void			pb(t_ab *ab);
void			ra(t_ab *ab);
void			rb(t_ab *ab);
void			rr(t_ab *ab);
void			rra(t_ab *ab);
void			rrb(t_ab *ab);
void			rrr(t_ab *ab);

#endif
