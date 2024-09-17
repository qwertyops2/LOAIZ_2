#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KOL_SIZE 7

int main(void)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	const int ARR_SIZE[KOL_SIZE] = { 100, 200, 400, 1000, 2000, 4000, 10000 };

	clock_t start, end; // объявляем переменные для определения времени выполнения
	double itog_vr;

	int i, j, r;
	int elem_c;

	printf("  Size |  Time\n-----------------------\n");

	for (int k = 0; k < KOL_SIZE; k++)
	{
		int size = ARR_SIZE[k];
		int** a = (int**)malloc(size * sizeof(int*));
		int** b = (int**)malloc(size * sizeof(int*));
		int** c = (int**)malloc(size * sizeof(int*));

		for (i = 0; i < size; i++)
		{
			a[i] = (int*)malloc(size * sizeof(int));
			b[i] = (int*)malloc(size * sizeof(int));
			c[i] = (int*)malloc(size * sizeof(int));
		}

		srand(time(NULL)); // инициализируем параметры генератора случайных чисел
		while (i < size)
		{
			while (j < size)
			{
				a[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
				j++;
			}
			i++;
		}
		srand(time(NULL)); // инициализируем параметры генератора случайных чисел
		i = 0; j = 0;
		while (i < size)
		{
			while (j < size)
			{
				b[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
				j++;
			}
			i++;
		}

		start = clock();
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				elem_c = 0;
				for (r = 0; r < size; r++)
				{
					elem_c = elem_c + a[i][r] * b[r][j];
					c[i][j] = elem_c;
				}
			}
		}
		end = clock();
		itog_vr = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;

		printf("%6d |  %lf\n", ARR_SIZE[k], itog_vr);

		for (i = 0; i < size; i++)
		{
			free(a[i]);
			free(b[i]);
			free(c[i]);
		}
		free(a);
		free(b);
		free(c);
	}
	return(0);
}