#include "../array/inc/array.h"

void			print(void **data, size_t i)
{
	int			*ptr;
	
	ptr = *data;
	printf("%d\n", *ptr);
}

void			shuffle(t_arr *arr, int n)
{
    if (n > 1) 
    {
        int i;
        srand(time(NULL));
        for (i = 0; i < n - 1; i++) 
        {
          int j = i + rand() / (RAND_MAX / (n - i) + 1);
          int *t = arr->data[j];
          arr->data[j] = arr->data[i];
          arr->data[i] = t;
        }
    }
}

int				main(int argc, char **argv)
{
	t_arr		out;
	size_t		size;
    int			i;
    int			*ptr;

	size = atoi(argv[1]);
	out = a_alloc(size);
    for (i = 0; i < size; i++)
	{
		ptr = (int *)malloc(sizeof(int));
		*ptr = i;
		a_add(&out, ptr);
    }
    shuffle(&out, size);
	a_iter(&out, print);
	printf("\n");
}

