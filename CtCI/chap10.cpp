#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//10.1
/*
void sorted_merge(int* a, int* b, int la, int lb)
{
	int size = la + lb - 1;
	la--;
	lb--;

	while (lb >= 0) {
		if (a[la] > b[lb]) {
			a[size--] = a[la--];
		} else {
			a[size--] = b[lb--];
		}
	}
}
void sorted_merge(int* a, int* b, int lastA, int lastB)
{
	int indexA = lastA - 1;
	int indexB = lastB - 1;
	int indexMerged = lastB + lastA - 1;

	while (indexB >= 0) {
		if (indexA >= 0 && (a[indexA] > b[indexB])) {
			a[indexMerged] = a[indexA];
			indexA--;
		}
		else {
			a[indexMerged] = b[indexB];
			indexB--;
		}
		indexMerged--;
	}
}*/
void sorted_merge(int* a, int* b, int lastA, int lastB)
{

	int index = lastA + lastB - 1;
	int indexA = lastA - 1;
	int indexB = lastB - 1;

	while ((indexA >= 0) && (indexB >= 0)) {
		if (a[indexA] > b[indexB]) {
			a[index] = a[indexA];
			indexA--;
		}
		else {
			a[index] = b[indexB];
			indexB--;
		}
		index--;
	}

	if (indexB > 0) {
		for (; indexB >= 0; indexB--) {
			a[index] = b[indexB];
			index--;
		}
	}
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
