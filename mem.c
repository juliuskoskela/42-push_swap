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

static int			v_cmp_words(const void *src, const void *cmp, size_t words)
{

	const size_t	*src64;
	const size_t	*dst64;

	src64 = (const size_t *)src;
	dst64 = (const size_t *)cmp;
    while (words-- && *dst64 == *src64)
	{
		dst64++;
		src64++;
	}
    return (*src64 - *dst64);
}

int					v_cmp2(const void *src, const void *cmp, const size_t size)
{

	const char		*src8;
	const char		*dst8;
	size_t			offset;
	size_t			words;
	int				ret;

	words = size / 8;
	offset = size - words * 8;
	if ((ret = v_cmp_words(src, cmp, words)) > 0)
		return (ret);
	src8 = (const char *)src;
	src8 = &src8[words * 8 - 1];
	dst8 = (const char *)cmp;
	dst8 = &dst8[words * 8 - 1];
	while (offset-- && src8 == dst8)
	{
		dst8++;
		src8++;
	}
	return (*src8 - *dst8);
}

void		*memdup(void *src, size_t size)
{
	void			*out = malloc(size);
	const size_t	*src64;
	size_t			*dst64;
	const char		*src8;
	char			*dst8;
	size_t			offset;
	size_t			bits;
	size_t			words;
	size_t			i;

	offset = (8 * size) % 64;
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
	i = size - offset / 8;
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
		/*ret = v_cmp2(src, dst, strlen(dst));*/
		/*ret = v_cmp(src, dst, strlen(dst));*/
		ret = s_cmp(src, dst);
		/*ret = memcmp(src, dst, strlen(src));*/
		if (ret != 0)
			printf("CHAOS");
		iters--;
	}
	end= clock();
	float seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("time elapsed folded: %f\n", seconds);
}

