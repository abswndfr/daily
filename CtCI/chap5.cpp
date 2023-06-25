#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>


void printBin(unsigned int a)
{
	for (int i = 31; i >= 0; i--)
		printf("%d", (a & (1 << i)) >> i);
	printf("\n");
}


int countOnes(unsigned int a)
{
	int count = 0;
/*
	   2 :  0010 0001	-> 0000		1

	   3 :  0011 0010   -> 0010
		    0010 0001   -> 0000		2

	   4 :  0100 0011	-> 0000		1

	   7 :  0111 0110	-> 0110
			0110 0101	-> 0100 
			0100 0011	-> 0000		3
*/
	while (a) {
		a = a & (a - 1);
		count++;
	}

	return count;
}


//prime
// 1. n = 4; n / 2 = 2 while i starts from 2 -> skip for loop
bool isPrime(int n)
{
/*
	if (n == 4) {
		return false;
	}
	else if (n < 6) {
		return true;
	}*/
	switch (n) {
	case 2:	case 3: case 5:
		return true;
	case 4:
		return false;
	}

	// n = 2	n/2 = 1		i =
	// n = 3	n/3	= 1		i =
	// n = 4	n/4	= 2		i =			
	// n = 5	n/5 = 2		i =
	// n = 6	n/6	= 3		i = 2..3
	// n = 7	n/7	= 3		i = 2..3
	// n = 8	n/8 = 4		i = 2..4
	for (int i = 2; i < n / 2; i++) {
		//printf("%d %d  ", n, i);
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}


bool find_prime(int n)
{
	return true;
}


// 1. *des++ &	*src++		!!!!
// 2. *(des+size)--	(X)		tmp = des+size; tmp--;
//*3. src + size : 6 not 5		 0123456		0123456		
//	  => src + size - 1		src	 hello0?	des =ello0? 
//	  or while(tmpS >= src) { tmpS--; ...}
char* myMemcpy(char* src, char* des, int size)
{
	/* original memcpy
	while (size--) {
		*des++ = *src++;
	}*/

	char* tmpS = src + size - 1;
	char* tmpD = des + size - 1;

	if (des < src || src + size < des) {	// des comes before src or des comes after src+size
		memcpy(des, src, size);
	}									
	else {
		//while (tmpS >= src) {				// && tmpD >= des)
		while (size--) {
			*(tmpD)-- = *(tmpS)--;
		}
	}

	return des;
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
	int mask = ((1 << (j + 1)) - 1) ^ ((1 << i) - 1);
	a = (a & ~mask) | (b << i);

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
	/* 1  1  0  1  1  0  0  1  1  1  1  1  0  0
	   1  1  0  1  1  0  1  1  1  1  1  1  0  0
	   1  1  0  1  1  0  1  0  0  0  1  1  1  1 */
	//** closet bigger number
	// find the right most non trailing zero and set to it
	bool oneFound = false;
	int bit = 0;	
	int b = a;
	bool zeroFound = false;
	int oneCount = 0;

	while (bit < 32) {
		// find 1 first
		if (b & (1<<bit)) {
			oneFound = true;
			oneCount++;
		}

		// then find 0 
		if (oneFound && !(b & (1 << bit))) {
			b |= 1<<bit;
			break;
		}
		bit++;
	}

	// clear after the 1st one and then set count - 1
	b = b & ~((1 << bit) - 1);
	for (int i = 0; i < oneCount - 1; i++) {
		b = b | 1 << i;
	}

	/* 1  0  0  1  1  1  1  0  0  0  0  0  1  1
	   1  0  0  1  1  1  0  0  0  0  0  0  0  0
	   1  0  0  1  1  1  0  1  1  1  0  0  0  0 */
	//** closet smaller number
	//find the right most non trailing zero and clear it


	bit = 0;
	oneCount = 0;
	while (bit < 32) {
		// find 0 first
		if (!(a & (1 << bit))) {
			zeroFound = true;
		}
		else {
			if (!zeroFound)
				oneCount++;
		}

		// then find 1 and clear it to zero
		if (zeroFound && (a & (1 << bit))) {
			a &= ~(1 << bit);
			break;
		}

		bit++;
	}

	// clear after the flipped bit and then set count + 1
	a = a & ~((1 << bit) - 1);

	//printf("%d %d %d..", a, bit, oneCount);
	for (int i = 0; i < oneCount + 1; i++) {
		a = a | 1 << (bit-1);
		bit--;
	}
	printf("%5d %5d\n", b, a);

	return countOnes(a);
}


//5.6
// count++ !!!!!!!!!!
int conversion(int a, int b)
{
	int count = 0;

	//printBin(a);
	//printBin(b);

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
	//printf("is prime?: %d\n", find_prime(7));
	printf("is 2 prime?: %d\n", isPrime(2));
	printf("is 3 prime?: %d\n", isPrime(3));
	printf("is 4 prime?: %d\n", isPrime(4));	// ????
	printf("is 5 prime?: %d\n", isPrime(5));
	printf("is 6 prime?: %d\n", isPrime(6));
	printf("is 7 prime?: %d\n", isPrime(7));
	printf("is 8 prime?: %d\n", isPrime(8));
	printf("is 9 prime?: %d\n", isPrime(9));


	char src[] = "hello";
	char* des = (char *)malloc(20);
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
	//printBin(bitInsert(0b10000000000, 0b10011, 2, 6));
	//printBin(bitInsert(0b10010110001, 0b1000, 3, 6));

	// 5.4										B		S
	printf("5.4\n");
	bigSmallFromGiven(5);		//  5: 0101		0110	0011		 6	3
	bigSmallFromGiven(9);		//  9: 1001		1010	0110		10	6	
	bigSmallFromGiven(11);		// 11: 1011		1101	0111		13	7	
	bigSmallFromGiven(13948);	//	

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
