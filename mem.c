#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include "string/inc/string.h"
#include "libft/inc/libft.h"

// mem_bytes = 3478
// mem_bits = 3478 * 8 = 27824
// mem_words = (3478 * 8) / 64 = 434
// mem_pages = mem_words / 4 = 108
//
// bit = 1
// byte = 8
// word = 64
// page = 256

int			v_cmp_words(void *src, void *cmp, size_t words)
{

	const size_t	*src64;
	size_t			*dst64;

	src64 = src;
	dst64 = cmp;
	while (words--)
	{
		if (dst64[words] != src64[words])
			return (1);
	}
	return (0);
}

int			v_cmp2(void *src, void *cmp, size_t size)
{

	const char		*src8;
	char			*dst8;
	size_t			rem;
	size_t			words;

	src8 = src;
	dst8 = cmp;
	rem = size % 8;
	words = size / 8;
	if (v_cmp_words(src, cmp, words))
		return (1);
	while (rem--)
	{
		if (dst8[size - rem] != src8[size - rem])
			return (1);
	}
	return (0);
}

int			v_cmp1(void *src, void *cmp, size_t size)
{

	const size_t	*src64;
	size_t			*dst64;
	const char		*src8;
	char			*dst8;
	size_t			rem;
	size_t			words;
	size_t			i;

	rem = size % 8;
	src64 = src;
	dst64 = cmp;
	src8 = src;
	dst8 = cmp;
	words = size / 8;
	while (words--)
	{
		if (dst64[words] != src64[words])
			return (1);
	}
	i = size - rem;
	while (i < size)
	{
		if (dst8[i] != src8[i])
			return (1);
		i++;
	}
	return (0);
}

void		*memdup(void *src, size_t size)
{
	void			*out = malloc(size);
	const size_t	*src64;
	size_t			*dst64;
	const char		*src8;
	char			*dst8;
	size_t			rem;
	size_t			bits;
	size_t			words;
	size_t			i;

	rem = (8 * size) % 64;
	bits = 8 * size;
	src64 = src;
	dst64 = out;
	src8 = src;
	dst8 = out;
	words = bits / 64;
	i = 0;

	while (i < words)
	{
		dst64[i] = src64[i];
		i++;
	}
	i = size - rem / 8;
	while (i < size)
	{
		dst8[i] = src8[i];
		i++;
	}
	return (out);
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
	dst = (char *)memdup(src, sizeof(char) * strlen(src));
	/*dst[0] = '0';*/
	/*dst[strlen(dst) -1] = '0';*/
	printf("%s\n", dst);
	printf("\nsizeof char %lu\n", sizeof(char));
	start = clock();
	while (iters)
	{
		ret = v_cmp2(src, dst, strlen(dst));
		/*ret = v_cmp(src, dst, strlen(dst));*/
		/*ret = s_cmp(src, dst);*/
		/*ret = memcmp(src, dst, strlen(src));*/
		if (ret == 1)
			printf("CHAOS");
		iters--;
	}
	end= clock();
	float seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("time elapsed folded: %f\n", seconds);
}

