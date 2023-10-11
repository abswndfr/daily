#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>


void printBin(unsigned int a)
{
	for (int i = 31; i >= 0; i--)
		printf("%d", (a & (1 << i)) >> i);
	printf("... %d\n", a);
}


int countOnes(unsigned int a)
{
	int count = 0;

	while(a > 0) {	
		a = a & (a - 1);		// 0b1_1000 & 0b1_0111 = 0b1_0000
		count++;
	}

	return count;
}


//prime
// 1. n = 4; n / 2 = 2 while i starts from 2 -> skip for loop
bool isPrime(int n)
{
	//for (int i = 2; i < n; i++) {

	// n = 2, 3, 5, 
	if (n == 4) return false;
	for (int i = 2; i < n/2; i++) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}

/*
	2	4,6,8,...
	3	6,9,12,...
	4	8,12,...
	5	10,15,...
*/
void find_prime(int n)
{
	bool *number = (bool*)malloc(sizeof(bool) * n);
	if (number) {
		memset(number, true, sizeof(bool) * n);

		for (int i = 2; i < n/2; i++) {	
			for (int p = i * 2; p < n; p+=i) {
				number[p] = false;
			}
		}

		for (int i = 0; i < n; i++) {
			if (number[i]) {
				printf("%d ", i);
			}	
		}
		printf("\n");
	}
}


// 1. *des++ &	*src++		!!!!
// 2. *(des+size)--	(X)		tmp = des+size; tmp--;
//*3. src + size : 6 not 5		 0123456		0123456		
//	  => src + size - 1		src	 hello0?	des =ello0? 
//	  or while(tmpS >= src) { tmpS--; ...}
char* myMemcpy(char* src, char* des, int size)
{
	//while (*src) {
	//	*des++ = *src++;
	//}

	// 0123456
	// helloN

	char* src_end = src + size - 1;
	char* des_end = des + size - 1;

	while (size--) {	
		*des_end-- = *src_end--;
	}

	return des; //  +size;
}



/*
void combinationUtil(int* arr, int* data, int start, int end, int index, int r)
{
}


void printCombination(int* arr, int n, int r)
{
}


void swap(char* x, char* y)
{
}


void permute(char* a, int l, int r)
{
}*/



//5.1
// i = 2, j = 6
// 9876543210
//    j   i 
// 
// 1110000011 *
//    1111111
//		   11
// 1. +/- has a higher precedence than <</>> : 1 << j - 1 vs. (1 << j) - 1	=> - first vs. << first	
// 2. b << i, not b << j
unsigned int bitInsert(unsigned int a, unsigned int b, int i, int j)
{
	// 9876543210	
	// 1101011011
/*
	(1<<(j+1))-1 = 0b001111111
	1<<i	-1	 = 0b000000011
	
*/
	int mask = ((1 << (j + 1)) - 1) ^ ((1 << i) - 1);
	a = a & (~mask);
	a = a | (b << i);

	return a;
}


//5.4
/*
13  12  11  10  9  8  7  6  5  4  3  2  1  0		more
---------------------------------------------
 1   1   0   1  1  0  0  1  1  1  1  1  0  0
					  ^
 1   1   0   1  1  0  1  1  1  1  1  1  0  0

 1   1   0   1  1  0  1  0  0  0  0  0  0  0
						 ^  ^  ^  ^  ^  ^  ^
 1   1   0   1  1  0  1  0  0  0  1  1  1  1
								  ^  ^  ^  ^

 13  12  11  10  9  8  7  6  5  4  3  2  1  0		less
 ---------------------------------------------
 1   0   0    1  1  1  1  0  0  0  0  0  1  1
					   ^
 1   0   0    1  1  1  0  0  0  0  0  0  0  0
										 ^  ^
 1   0   0    1  1  1  0  1  1  1  0  0  0  0
						  ^  ^  ^
*/
//	b |= bit; (X)    b |= 1<<bit;  (O)
//	set oneCount+1 not zeroCount+1 for smaller closest number 
unsigned int bigSmallFromGiven(unsigned int a)
{
	int c = a;
	int c0 = 0;
	int c1 = 0;

	// next
	while ((c & 1) == 0 && c)    {
		c = c >> 1;
		c0++;
	}

	while ((c & 1)) {
		c = c >> 1;
		c1++;
	}

	printBin(a);
	c = a;

	int p = c0 + c1;
	a = a | (1 << p);
	a = a & ~((1 << p) - 1);
	for (int i = 0; i < c1 - 1; i++) {
		a = a | 1 << i;
	}
	printBin(a);

	// previous
	a = c;
	c0 = 0;
	c1 = 0;

	while ((c & 1) && c) {
		c = c >> 1;
		c1++;
	}

	while ((c & 1) == 0 && c) {
		c = c >> 1;
		c0++;
	}

	p = c0 + c1;
	a = a & ~(1 << p);
	a = a & ~((1 << p) - 1);
	for (int i = 0; i < c1+1; i++) {
		a = a | (1 << (p-1-i));
	}

	printBin(a);
	printf("----------------\n");

	return a;
}


//5.6
// count++ !!!!!!!!!!
int conversion(int a, int b)
{
	int count = 0;

	a = a ^ b;

	while (a) {	
		a = a & (a - 1);
		count++;	
	}

	return count;
}





int main()
{
	// 1s
	printf("%d has %d 1s...", 35, countOnes(35));		printBin(35);
	printf("%d has %d 1s...", 31, countOnes(31));		printBin(31);

	// prime
	find_prime(100);

	printf("is 2 prime?: %d\n", isPrime(2));
	printf("is 3 prime?: %d\n", isPrime(3));
	printf("is 4 prime?: %d\n", isPrime(4));	// ????
	printf("is 5 prime?: %d\n", isPrime(5));
	printf("is 6 prime?: %d\n", isPrime(6));
	printf("is 7 prime?: %d\n", isPrime(7));
	printf("is 8 prime?: %d\n", isPrime(8));
	printf("is 9 prime?: %d\n", isPrime(9));


	char src[] = "hello";
	char* des = (char*)malloc(20);
	char* des_org;

	des_org = des;

	printf("src                 :%p %s(%d)\n", src, src, (int)sizeof(src));
	printf("new des(before copy):%p %s \n", des, des);
	des = myMemcpy(src, des, sizeof(src));
	printf("new des(after copy) :%p %s  \n", des, des);
	printf("org des             :%p %s\n\n\n", des_org, des_org);




#if 0
	// permutation
	printf("string permutation\n");
	char s[] = "ABC";
	int n = strlen(s);
	permute(s, 0, n - 1);

	// combination
	printf("combination\n");
	int comb[4] = { 10,20,30,40 };
	printCombination(comb, 4, 2);
#endif


	// 5.1
	printf("5.1\n");
	printBin(bitInsert(0b11111111111, 0b01011, 2, 6));
	printBin(bitInsert(0b10000000000, 0b10011, 2, 6));
	printBin(bitInsert(0b10010110001, 0b1000, 3, 6));

	// 5.4										B		S
	printf("5.4\n");
	bigSmallFromGiven(5);		//  5: 0101		0110	0011		 6	3
	bigSmallFromGiven(9);		//  9: 1001		1010	0110		10	6	
	bigSmallFromGiven(11);		// 11: 1011		1101	0111		13	7	
	bigSmallFromGiven(13948);	//     11011001111100				13967   13946

	// 5.6		29 (or: 11101), 15 (or: 01111) -> 2	
	printf("5.6   %d %d -> %d\n", 29, 15, conversion(29, 15));

	int testa = ~0;

	testa = testa & ~((1 << 6) - 1);
	printBin(testa);

	testa = ~0;
	testa = testa & ~((1 << 7) - 1);
	printBin(testa);




	return 0;
}
