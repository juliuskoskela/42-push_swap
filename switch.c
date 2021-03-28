#include <stdio.h>
# define FOO 0
# define BAR 1

void		foo(void)
{
	printf("foo\n");
}

void		bar(void)
{
	printf("foo\n");
}

int		main(void)
{
	void	*arr[2];
	void	(*fptr)(void);

	arr[FOO] = &foo;
	arr[BAR] = &bar;

	int flag = BAR;
	fptr = arr[flag];
	fptr();
}
