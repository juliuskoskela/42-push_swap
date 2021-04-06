# include "libft/inc/libft.h"
# define X &s_len

int main(void)
{
	char *str = "abc";
	uint64_t (*fptr)(const char *) = s_len;
	printf("%zu", fptr(str));
}
