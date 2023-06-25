#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printBin(unsigned int a)
{
	for (int i = 6; i >= 0; i--)
		printf("%d", (a & (1 << i)) >> i);
	printf("  ");
}


int countOnes(unsigned int a)
{
	int count = 0;
	/*
		for (int i = 0;i < 32; i++) {
			if (a & (1 << i)) {
				count++;
			}
		}*/
		/*
			while (a) {
				if(a & 1) {
					count++;	// count += a & 1;
				}
				a = a >> 1;
			}
		*/
	while (a) {
		a = a & (a - 1);
		count++;
	}

	return count;
}



//prime
bool prime(int n)
{
	/*
		for () {


		}
	*/
	return true;
}


bool find_prime(int n)
{
	return true;
}


//memcpy
char* mymemcpy(char* src, char* desc, int size)
{
	return desc;
}


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
}




//5.1
unsigned int bitInsert(unsigned int a, unsigned int b, int i, int j)
{
	int mask = ((1 << j) - 1) ^ ((1 << i) - 1);
	return a & (~mask) | (b << i);
}


//5.4
/*
13  12  11  10  9  8  7  6  5  4  3  2  1  0
---------------------------------------------
 1   1   0   1  1  0  0  1  1  1  1  1  0  0
					  ^
 1   1   0   1  1  0  1  1  1  1  1  1  0  0

 1   1   0   1  1  0  1  0  0  0  0  0  0  0
						 ^  ^  ^  ^  ^  ^  ^
 1   1   0   1  1  0  1  0  0  0  1  1  1  1
								  ^  ^  ^  ^
	int c = a;
	int c0 = 0;
	int c1 = 0;

	while (((c & 1) == 0) && (c != 0)) {	// trailing zero
		c0++;
		c >>= 1;
	}

	while ((c & 1) == 1) {					// non trailing ones
		c1++;
		c >>= 1;
	}

	printf("c0:%d c1:%d\n", c0, c1);
	// If there is no bigger number with the same no. of 1's
	if (c0 + c1 == 31 || c0 + c1 == 0)
		return -1;

	// position of rightmost non-trailing zero
	int p = c0 + c1;

	// Flip rightmost non-trailing zero
	a |= (1 << p);

	// Clear all bits to the right of p
	a &= ~((1 << p) - 1);

	// Insert (c1-1) ones on the right.
	a |= (1 << (c1 - 1)) - 1;

	return a;

 13  12  11  10  9  8  7  6  5  4  3  2  1  0
 ---------------------------------------------
 1   0   0    1  1  1  1  0  0  0  0  0  1  1
					   ^
 1   0   0    1  1  1  0  0  0  0  0  0  0  0
										^  ^
 1   0   0    1  1  1  0  1  1  1  0  0  0  0
						  ^  ^  ^

	int temp = a;
	int c0 = 0;
	int c1 = 0;

	// count 1s
	while ((temp & 1) == 1) {
		c1++;
		temp = temp >> 1;
	}

	if (temp == 0) {
		return -1;
	}

	// count 0s except leading 0s
	while (((temp & 1) == 0) && (temp != 0)) {
		c0++;
		temp = temp >> 1;
	}

	// position of rightmost non-trailing one.
	int p = c0 + c1;

	// clears from bit p onwards
	a = a & ((~0) << (p + 1));

	// Sequence of (c1+1) ones
	int mask = (1 << (c1 + 1)) - 1;

	a = a | mask << (c0 - 1);

	return a;
*/
unsigned int bigSmallFromGiven(unsigned int a)
{
/* 1  1  0  1  1  0  0  1  1  1  1  1  0  0
   1  1  0  1  1  0  1  1  1  1  1  1  0  0
   1  1  0  1  1  0  1  0  0  0  1  1  1  1 */
	//-- closet bigger number
	// find the right most non trailing zero and set to it
	bool oneFound = false;
	int bit = 0;
	int temp = a;
	int count = 0;

	while (bit < 32) {
		// find 1 first
		if (temp & (1 << bit)) {
			oneFound = true;
		}

		// then find 0 
		if (oneFound) {
			if (!(temp & (1 << bit))) {
				temp |= 1 << bit;
				break;
			}
			count++;
		}
		bit++;
	}

	// clear after the 1st one and then set count - 1
	temp = temp & ~((1 << bit) - 1);
	for (int i = 0; i < count - 1; i++) {
		temp |= 1 << i;
	}


/* 1  0  0  1  1  1  1  0  0  0  0  0  1  1
   1  0  0  1  1  1  0  0  0  0  0  0  0  0
   1  0  0  1  1  1  0  1  1  1  0  0  0  0 */

	//-- closet smaller number
	// find the right most non trailing one and set it
	int zeroFound = false;
	bit = 0;
	temp = a;
	count = 0;

	printBin(temp);

	while (bit < 32) {
		// find 0 first
		if (!(temp & (1 << bit))) {
			zeroFound = true;
		}

		// then find 1 and clear the bit
		if (zeroFound) {
			if (temp & (1 << bit)) {
				temp &= ~(1 << bit);
				break;
			}
		}
		else {
			count++;
		}
		bit++;
	}
	printf("..%d..", count);
	printBin(temp);

	// clear after the flipped bit and then set count + 1
	temp = temp & ~((1 << bit) - 1);
	printBin(temp);
	for (int i = 0; i < count + 1; i++) {
		temp |= 1 << (bit - i - 1);
	}
	printBin(temp);

	return temp;
}


//5.6
int conversion(int a, int b)
{
	int t;
	int	count = 0;

	t = a ^ b;

	while (t) {
		t = t & (t - 1);
		count++;
	}

	return count;
}





int main()
{
	// permutation
	printf("string permutation\n");
	char s[] = "ABC";
	int n = strlen(s);
	permute(s, 0, n - 1);

	// combination
	printf("combination\n");
	int comb[4] = { 10,20,30,40 };
	printCombination(comb, 4, 2);

	// prime
	printf("is prime?: %d\n", find_prime(7));


// 5.1
	printf("5.1\n");
	printBin(bitInsert(0b10000000000, 0b10011, 2, 6));
	printBin(bitInsert(0b10010110001, 0b1000, 3, 6));
	


// 5.4																B		S
	printf("\n5.4 count:%d\n", bigSmallFromGiven(5));		//  5: 0101		0110	0011		
	printf("\n5.4 count:%d\n", bigSmallFromGiven(9));		//  9: 1001		1010	0110		
	printf("\n5.4 count:%d\n", bigSmallFromGiven(11));	// 11: 1011		1101	0111			
	printf("\n5.4 count:%d\n", bigSmallFromGiven(13948));	


// 5.6		29 (or: 11101), 15 (or: 01111) -> 2	
	printf("5.6   %d %d -> %d\n", 29, 15, conversion(29,15));
	

	return 0;
}
