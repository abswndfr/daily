#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printBin(unsigned int a)
{
	for (int i = 31; i >= 0; i--)
		printf("%d", (a & (1 << i)) >> i);
	printf("\n");
}


int countOnes(unsigned int a)
{
	int count = 0;

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
	if ((n == 0) || (n == 1) || (n == 4)) {
		return false;
	}

	for (int i = 2; i < n / 2; i++) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}


void find_prime(int n)
{
	for (int i = 0; i < n; i++) {
		printf("%d is a prime number:%d\n", i, isPrime(i));
	}
}


// 1. *des++ &	*src++		!!!!
// 2. *(des+size)--	(X)		tmp = des+size; tmp--;
//*3. src + size : 6 not 5		 0123456		0123456		
//	  => src + size - 1		src	 hello0?	des =ello0? 
//	  or while(tmpS >= src) { tmpS--; ...}
char* myMemcpy(char* src, char* des, int size)
{
	/*
		src			---------						---------				  -----------
		des						---------				 ---------		----------
	*/
	if (0) {// (des < src) || (des > src + size)) {
		while (size) {
			*des++ = *src++;
			size--;
		}
	}
	else {
		src = src + size - 1;
		des = des + size - 1;

		while (size) {
			*des-- = *src--;
			size--;
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
*/



vector<string> permu(string s)
{
	//cout << s << "---> ";
	vector<string> result;

	// base case
	if (s.length() == 0) {
		//cout << "len = 0" << endl;
		// without this line, adding the 1st char fail in the for loop above leading no change in the upper call upon returning.
		//result.push_back("");
		return result;
	}
	//else
		//cout << "len = " << s.length() << endl;

	// take 1st char
	string c = s.substr(0, 1);
	//cout << "(" << c << ")";

	// get permutation with the remainder
	vector<string> subs = permu(s.substr(1));
	//cout << "subs size:" << subs.size() << endl;

	// iteration at current level
	for (int i = 0; i < subs.size(); i++) {
		// get each element
		string sub = subs[i];
		// place 1st char at every possible poistion
		for (int j = 0; j <= sub.length(); j++) {
			string sub_temp = sub;
			sub_temp.insert(j, c);
			result.push_back(sub_temp);
		}
	}

	// without this line, adding the 1st char fail in the for loop above leading no change in the upper call upon returning.
	if (subs.size() == 0) {
		result.push_back(c);
	}

	return result;
}



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
	/*
		9876543210
		0001111100
		   1111111
				11

	*/
	int mask = 0;
	//  9876543210
	mask = (1 << j);					//	   1000000	
	mask = mask | ((1 << j) - 1);		//     1111111
	mask = mask ^ ((1 << i) - 1);		//	   0000011	
	//     1111100 	
	a = a & ~mask;
	a = a | b << i;

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
		   // find 1 first
		   // then find 0 
	int b = a;
	int i = 0;
	int len = sizeof(int) * 8;
	int bit = 0;
	bool found = false;
	int count = 0;

	printBin(a);

	while (i < len) {
		bit = 1 << i;
		if (a & bit) {
			count++;
			found = true;
		}

		if ((found) && (!(a & bit))) {
			a |= bit;
			break;
		}

		i++;
	}

	a &= ~(bit - 1);

	for (int j = 0; j < count - 1; j++) {
		a |= 1 << j;
	}

	printBin(a);

	/* 1  0  0  1  1  1  1  0  0  0  0  0  1  1
		1  0  0  1  1  1  0  0  0  0  0  0  0  0
		1  0  0  1  1  1  0  1  1  1  0  0  0  0 */
		//** closet smaller number
		//find the right most non trailing zero and clear it
			// find 0 first
			// then find 1 and clear it to zero
		// clear after the flipped bit and then set count + 1
	i = 0;
	count = 0;
	found = false;
	a = b;

	while (i < len) {
		bit = 1 << i;
		if (a & bit) {
			count++;
			if (found) {
				a &= ~bit;
				break;
			}
		}

		if (!(a & bit)) {
			found = true;
		}
		i++;
	}

	a &= ~(bit - 1);

	for (int j = 0; j < count; j++) {
		a |= 1 << (i - j - 1);
	}

	printBin(a);
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
	//printf("is prime?: %d\n", find_prime(7));
	printf("is 2 prime?(1): %d\n", isPrime(2));
	printf("is 3 prime?(1): %d\n", isPrime(3));
	printf("is 4 prime?(0): %d\n", isPrime(4));	// ????
	printf("is 5 prime?(1): %d\n", isPrime(5));
	printf("is 6 prime?(0): %d\n", isPrime(6));
	printf("is 7 prime?(1): %d\n", isPrime(7));
	printf("is 8 prime?(0): %d\n", isPrime(8));
	printf("is 9 prime?(0): %d\n", isPrime(9));

	find_prime(20);

	char src[] = "hello";
	char* des = (char*)malloc(20);
	char* des_org;

	des_org = des;

	printf("src                 :%p %s(%d)\n", src, src, (int)sizeof(src));
	printf("new des(before copy):%p %s \n", des, des);
	des = myMemcpy(src, des, sizeof(src));
	printf("new des(after copy) :%p %s  \n", des, des);
	printf("org des             :%p %s\n\n\n", des_org, des_org);


	// permutation
	string s = "abc";
	vector<string> res = permu(s);

	for (int i = 0; i < res.size(); ++i)
		cout << res[i] << endl;

#if 0
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
