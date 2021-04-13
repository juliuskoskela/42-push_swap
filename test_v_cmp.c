# include "libft/inc/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

int			naive_memcmp(const void *src, const void *cmp, size_t bytes)
{
	const unsigned char		*str1;
	const unsigned char		*str2;

	if (src == cmp || bytes == 0)
		return (0);
	str1 = (const unsigned char *)src;
	str2 = (const unsigned char *)cmp;
	while (bytes--)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		if (bytes)
		{
			str1++;
			str2++;
		}
	}
	return (0);
}

int			main(void)
{
	char	*src;
	char	*dst;
	clock_t start;
	clock_t end;
	size_t	iters = 10000000;
	int ret;

	src = "1111111162345789999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999000111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
	dst = s_dup(src);
	dst[0] = '0';
	/*dst[strlen(dst) -1] = '0';*/
	printf("%s\n", dst);
	printf("\nsizeof char %lu\n", sizeof(char));
	start = clock();
	while (iters)
	{
		/*ret = v_cmp2(src, dst, strlen(dst));*/
		/*ret = v_cmp(src, dst, s_len(dst));*/
		ret = naive_memcmp(src, dst, s_len(dst));
		/*ret = s_cmp(src, dst);*/
		/*ret = memcmp(src, dst, s_len(src));*/
		if (ret != 0)
			printf("CHAOS");
		iters--;
	}
	end= clock();
	float seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("time elapsed folded: %f\n", seconds);
}


