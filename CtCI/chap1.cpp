#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//1.1
// init bitmap after creating
// while(*str), not while(str)
#define ASCII_CODE_SIZE		128
bool isUnique(char* str)
{
	bool* letters = (bool *)malloc(sizeof(bool) * ASCII_CODE_SIZE);
	memset(letters, false, sizeof(bool) * ASCII_CODE_SIZE);

	bool isFound = false;

	while (*str) {	
		if (letters[*str]) {
			return false;		
		}
		else {
			letters[*str] = true;
		}

		str++;
	}

	return true;
}

//1.2
// is each character unique ? boolean type if yes, int type if no.
bool isPermutation(char* strA, char* strB)
{
	int* letters = (int*)malloc(sizeof(int) * ASCII_CODE_SIZE);
	memset(letters, 0, sizeof(int) * ASCII_CODE_SIZE);

	while (*strA) {
		letters[*strA]++;
		strA++;
	}

	while (*strB) {
		letters[*strB]--;
		if (letters[*strB] < 0) {
			return false;
		}
		strB++;
	}

	return true;
}

//1.4
// is null string a palindrome ? 
// reinit ptr after string reaches '/0' -> or use for instead while w/ str++
bool isPalindromePermutation(char* str)
{
	int* letters = (int*)malloc(sizeof(int) * ASCII_CODE_SIZE);
	memset(letters, 0, sizeof(int) * ASCII_CODE_SIZE);

	bool isOddFound = false;

	while (*str) {
		letters[*str]++;
		str++;
	}

	for (int i = 0; i < ASCII_CODE_SIZE; i++) {
		if (letters[i] % 2 == 1) {
			if (isOddFound) {
				return false;
			}
			else {
				isOddFound = true;
			}
		}
	}

	return true;
}

#define MAX(A, B)		((A) > (B) ? (A) : (B))
#define ABS(A)			((A) > 0 ? (A) : (A) * (-1))

//1.5 char edit like insert, remove, or replace => same str?
// move next in one string only if lenA != lenB
// asdfjkl & asejkl : 2 edits away(replace & insert) -> needs 'continue'
bool isOneEditAway(char* strA, char* strB)
{
	int lenA = strlen(strA);
	int lenB = strlen(strB);
	bool isMismatchFound = false;

	if (ABS(lenA - lenB) > 1) {
		return false;
	}

	while (*strA) {
		if (*strA != *strB) {
			if (isMismatchFound) {
				return false;
			}

			isMismatchFound = true;

			if (lenA > lenB) {
				strA++;
				continue;
			}
			else if (lenA < lenB) {
				strB++;
				continue;
			}
			else {

			}
		}
		strA++;
		strB++;

	}

	return true;
}

//1.6
// index should be the current one at the bottom of for loop. It will advance at the top of for loop.

/*
 	0123456789012345678
	aaabbbbbcddddeefffk
	  i
	  j
c   123
*/
char* string_compression(char* str)
{
	int len = strlen(str);
	int count;

	for (int i = 0; i < len; i++) {
		count = 1;
		printf("%c", str[i]);

		if (i==len-1) {
		
		}
		else {
			if (str[i] == str[i + 1]) {
				count = 2;
				for (int j = i + 1; j < len-1; j++) {
					i = j;
					if (str[j] != str[j + 1]) {
						break;
					}
					count++;
				}
			}
		}

		printf("%d",count);
	}

	printf("\n");

	return str;
}


//1.7 
// cw : transpose -> swap columns
// ccw: transpose -> reverse columns
/*
void rotate(vector<vector<int>>& matrix) {

}*/

//1.8
bool zero_matrix(int** matrix, int len)
{
	return true;
}

//1.9
bool string_rotation(char* stra, char* strb)
{
	return true;
}




int main()
{
	char astr[] = "asdfjkl";
	char bstr[] = "asefjkl";	// asefjkl
	char cstr[] = "aaabbbbbcddddeefffk"; // aaabbbbbcddddeefffk


	// 1.1
	if (isUnique(astr)) {
		printf("1.1 no dup found\n");
	}
	else {
		printf("1.1 dup found\n");
	}

	// 1.2
	if (isPermutation(astr, bstr)) {
		printf("1.2 permutation\n");
	}
	else {
		printf("1.2 not permutation\n");
	}

	// 1.4
	if (isPalindromePermutation(bstr)) {
		printf("1.4 permutation of palindrome\n");
	}
	else {
		printf("1.4 not permutation of palindrome\n");
	}

	// 1.5
	if (isOneEditAway(astr, bstr)) {
		printf("1.5 one edit away\n");
	}
	else {
		printf("1.5 more than one edit away\n");
	}

	// 1.6
	printf("\n1.6 %s", string_compression(cstr));


	return 0;
}
