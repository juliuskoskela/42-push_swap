# include <stdio.h>
# include <stdlib.h>

void	print_arr(int a[], int n)
{
	int		i;

	i = 0;
	printf("{ ");
    while (i < n - 1)
	{
		printf("%d, ", a[i]);
		i++;
	}
	printf("%d", a[i]);
	printf(" }\n");
}
// Generating permutation using Heap Algorithm
void	heap_permutation(int a[], int size, int n)
{
    // if size becomes 1 then prints the obtained
    // permutation
	int		tmp;
	int		i;

	tmp = 0;
    if (size == 1)
	{
        print_arr(a, n);
        return ;
    }
	i = 0;
    while (i < size)
	{
        heap_permutation(a, size - 1, n);
        // if size is odd, swap 0th i.e (first) and
        // (size-1)th i.e (last) element
        if (size % 2 == 1)
		{
			tmp = a[0];
			a[0] = a[size - 1];
			a[size - 1] = tmp;
		}
        // If size is even, swap ith and
        // (size-1)th i.e (last) element
        else
		{
			tmp = a[i];
			a[i] = a[size - 1];
			a[size - 1] = tmp;
		}
		i++;
    }
}

int			main(int argc, char **argv)
{
	int		size;
	int		i;
	int		*a;

	size = atoi(argv[1]);
	a = (int *)malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		a[i] = i;
		i++;
	}
    heap_permutation(a, size, size);
	free(a);
    return 0;
}
