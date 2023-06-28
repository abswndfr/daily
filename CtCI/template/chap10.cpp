#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//10.1
void sorted_merge(int* a, int* b, int lastA, int lastB)
{
}




int main()
{
	// 10.1
	printf("10.1\n");
	int b[5] = { 1, 3,12,14,25 };
	int a[20] = { 7,11,13,14,15 };

	sorted_merge(a, b, 5, 5);

	for (int i = 0; i < 20; i++) {
		printf("%3d ", a[i]);

		if ((i + 1) % 10 == 0) printf("\n");
	}

	return 0;
}
