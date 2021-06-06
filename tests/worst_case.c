// C program to generate Worst Case of Merge Sort
#include <stdlib.h>
#include <stdio.h>

// Function to print an array
void	print_array(int A[], int size)
{
	for (int i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

// Function to join left and right subarray
int	join(int arr[], int left[], int right[],
		int l, int m, int r)
{
	int i; // Used in second loop
	for (i = 0; i <= m - l; i++)
		arr[i] = left[i];

	for (int j = 0; j < r - m; j++)
		arr[i + j] = right[j];
}

// Function to store alternate elemets in left
// and right subarray
int	split(int arr[], int left[], int right[],
		int l, int m, int r)
{
	for (int i = 0; i <= m - l; i++)
		left[i] = arr[i * 2];

	for (int i = 0; i < r - m; i++)
		right[i] = arr[i * 2 + 1];
}

// Function to generate Worst Case of Merge Sort
int	generate_worst_case(int arr[], int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;

		// create two auxiliary arrays
		int left[m - l + 1];
		int right[r - m];

		// Store alternate array elements in left
		// and right subarray
		split(arr, left, right, l, m, r);

		// Recurse first and second halves
		generate_worst_case(left, l, m);
		generate_worst_case(right, m + 1, r);

		// join left and right subarray
		join(arr, left, right, l, m, r);
	}
}

int	*generate_array(int size)
{
	int	*out;
	int	i;

	out = malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		out[i] = i;
		i++;
	}
	return (out);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	int	n = atoi(argv[1]);
	int	*arr = generate_array(n);
	generate_worst_case(arr, 0, n - 1);
	print_array(arr, n);
	return (0);
}
