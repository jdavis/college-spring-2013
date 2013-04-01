#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9},
	}

	int b[3][3];
	int result[3][3];
	int i, j, k;

	printf("for\n");
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			result[i][j] = 0;
			for(k = 0; k < 3; k++) {
				printf("%i*%i + ", across[k], down[k]);
				result[i][j] += a[i][k] * down[k][j];
			}
			printf("\n");
		}
	}

	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++)
			printf("%i ", result[i][j]);
		printf("\n");
	}

	return 0;
}
