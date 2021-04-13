# include "libft/inc/libft.h"
# define X &s_len
# define PROJ_MAT g_proj

typedef struct	s_ptrs
{
	void		(*print)(t_vct4, size_t);
}				t_ptr;
int main(void)
{
	char *str = "abc";
	uint64_t (*fptr)(const char *) = s_len;
	printf("%zu", fptr(str));
}
