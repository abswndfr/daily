#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//8.1
int triple_step(int n)
{
	return ...
}

int triple_steps(int n)
{
	return ...
}


//8.2
int arr[3][3];

//-1:block, 0:can move, >1 :visited
bool robotInGrid(int row, int col, int step)
{
	return true;
}

void printArray(int* data, int r)
{
	for (int j = 0; j < r; j++)
		printf("%d ", data[j]);
	printf("\n");
}


//8.4
#include <math.h>
void pow_set(int set_size)
{
}


//8.5
int multiply(int a, int b)
{
	return a;
}



int main()
{
	// 8.2
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			arr[i][j] = 0;
		}
	}
	arr[1][1] = -1;

	if (robotInGrid(0, 0, 0)) {
		printf("pass\n");
	}
	else {
		printf("fail\n");
	}

	// 8.4
	pow_set(3);

	// 8.5
	printf("%d\n", multiply(10, 20));


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}
