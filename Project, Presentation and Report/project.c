#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXN 8000 // Max number of vertices
int matrix[MAXN][MAXN];
int row, column, n;

void fill(void);   // fill the adjacency matrix randomly
void result(void); // calculate In-Degree and Out-Degree
int main()
{
	clock_t start, end;
	double elapsed;
	start = clock();
	printf("Enter the amount of Vertices: ");
	scanf("%d", &n);

	start = clock();
	fill();
	result();
	end = clock();
	elapsed = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
	printf("Time taken: %.2f ms.\n", elapsed);
	return 0;
}

void fill()
{
	srand((unsigned)time(NULL));
	for (row = 0; row < n; row++)
	{
		for (column = 0; column < n; column++)
		{
			matrix[row][column] = rand() % 2;
		}
	}
}

void result()
{
	int in_degree = 0, out_degree = 0;
	for (row = 0; row < n; row++)
	{
		for (column = 0; column < n; column++)
		{
			in_degree += matrix[column][row];
		}
	}

	for (row = 0; row < n; row++)
	{
		for (column = 0; column < n; column++)
		{
			out_degree += matrix[row][column];
		}
	}

	printf("Total In-Degree: %d\n", in_degree);
	printf("Total Out-Degree: %d\n", out_degree);

	if (in_degree != out_degree)
	{
		printf("Sum of In Degree and Out Degree are not Equal\n");
	}
	else
	{
		printf("Sum of In Degree and Out Degree are Equal\n");
	}
}